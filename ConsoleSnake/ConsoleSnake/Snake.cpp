/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Source file for drawing and managing player (snake) behavior.
 */

#include <conio.h>
#include <iostream>
#include <iomanip>
#include "../Headers/Snake.h"
#include "../Headers/Timer.h"
#include "../Headers/Stage.h"
#include "../Headers/Game.h"
#include "../Headers/GridMap.h"
#include "../Headers/Food.h"

using std::cout;
using std::endl;

Snake::Snake(UI& ref)
	: refUi(ref), MoveUp({ 0, -1 }), MoveDown({ 0, 1 }), MoveLeft({ -2, 0 }), MoveRight({ 2, 0 }), BodyInitialAmount(0)
{
	isGameOver = false;
}

void Snake::setupMovementBoundaries(Point& refStartPosition, Point& refEndPosition)
{
	startMovePosition = Game::StartScreenPoint; //3,1
	endMovePosition = Game::EndScreenPoint; //111,32

	// ADJUSTS FOR KEEP MOVEMENT INSIDE GRID LIMITS
	startMovePosition += {16, 8}; //19,9
	endMovePosition -= {16, 7}; //95,25

	refStartPosition = Point(startMovePosition);
	refEndPosition = Point(endMovePosition);

	createSnakeHead();
	/*Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
	Game::setCursorPosition(Point(21, 10));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(19, 21));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(25, 14));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(57, 17));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(65, 9));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(79, 9));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(91, 24));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(93, 20));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(93, 25));
	cout << Food::FoodCharacter;
	Game::setCursorPosition(Point(95, 13));
	cout << Food::FoodCharacter;*/

	Timer::setTimerAndCallback(50, this, &Snake::processesInputs_callBack);
	Timer::setTimerAndCallback(refUi.getSpeedPanelValue(), this, &Snake::movesTheSnake_callBack);
}

bool Snake::processesGameplay()
{
	Timer::run();

	if (isGameOver)
	{
		Timer::markTimerForDeletion(this, &Snake::processesInputs_callBack);
		Timer::markTimerForDeletion(this, &Snake::movesTheSnake_callBack);
		refUi.deleteUItimers();
		body.clear();
	}

	return !isGameOver;
}

int Snake::processesInputs()
{
	short key = 0;

	if (_kbhit())
	{
		key = _getch();

		if (key == static_cast<short>(KeyValues::SpecialKey1) ||
			key == static_cast<short>(KeyValues::SpecialKey2))
		{
			key = _getch(); // One more reading is needed to get the actual key pressed.
		}

		switch (key)
		{
			case 'w':
			case 'W':
			case static_cast<short>(KeyValues::ArrowUp):
				if (lastMovementDirection != MoveDown) movementDirection = MoveUp;
				break;

			case 'a':
			case 'A':
			case static_cast<short>(KeyValues::ArrowLeft):
				if (lastMovementDirection != MoveRight) movementDirection = MoveLeft;
				break;

			case 'd':
			case 'D':
			case static_cast<short>(KeyValues::ArrowRight):
				if (lastMovementDirection != MoveLeft) movementDirection = MoveRight;
				break;

			case 's':
			case 'S':
			case static_cast<short>(KeyValues::ArrowDown):
				if (lastMovementDirection != MoveUp) movementDirection = MoveDown;
				break;

			default:
				break;
		}
	}

	return key;
}

void Snake::createSnakeHead()
{
	// RANDOMLY POSITIONS THE "HEAD" ON THE MAP
	const short xCoordLimit = static_cast<short>((endMovePosition.X() - startMovePosition.X()) * 0.5) + 1;
	const short yCoordLimit = static_cast<short>(endMovePosition.Y() - startMovePosition.Y() + 1);
	
	short randomXcoord, randomYcoord;

	randomXcoord = (rand() % xCoordLimit); // Seed has already been generated with srand in the Game constructor.
	randomYcoord = (rand() % yCoordLimit);

	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightAqua);
	head = BodyPiece(startMovePosition + Point(randomXcoord * 2, randomYcoord), '@');
	head.printBodyPiece();

	// DETERMINES THE DIRECTION OF THE SNAKE'S MOVEMENT
	Point centerPosition = {
		static_cast<int>((startMovePosition.X() + endMovePosition.X()) * 0.5),
		static_cast<int>((startMovePosition.Y() + endMovePosition.Y()) * 0.5) };

	movementDirection = centerPosition - head.getPosition();

	if (abs(movementDirection.X()) > abs(movementDirection.Y()))
		movementDirection = { (movementDirection.X() / abs(movementDirection.X())) * 2, 0 }; // {2,0} or {-2,0}
	else if (abs(movementDirection.Y()) > abs(movementDirection.X()))
		movementDirection = { 0, movementDirection.Y() / abs(movementDirection.Y()) }; // {0,1} or {0,-1}
	else
	{
		// Choose direction in "x" or "y" randomly.
		if (((rand() % 100) % 2) == 0)
			movementDirection = { (movementDirection.X() / abs(movementDirection.X())) * 2, 0 }; // {2,0} or {-2,0}
		else
			movementDirection = { 0, movementDirection.Y() / abs(movementDirection.Y()) }; // {0,1} or {0,-1}
	}

	createSnakeBody();
}

void Snake::createSnakeBody()
{
	Point oppositeMovementDirection = movementDirection * -1;
	Point lastOppositeDirection = head.getPosition();

	//short keyForDebugCaseTest = _getch();

	// Lambda expression to check collision during body drawing.
	auto checkForOppositeCollision = [&oppositeMovementDirection, &lastOppositeDirection, this] ()
	{
		bool hadCollision = false;

		// Changes the axis of the opposite direction if it is going to collide.
		if ((!body.empty() && Game::getCursorPositionData(lastOppositeDirection) == body.front().getBodySymbol())
			|| Game::getCursorPositionData(lastOppositeDirection) == Stage::BorderCharacter
			|| Game::getCursorPositionData(lastOppositeDirection) == head.getBodySymbol()
			|| GridMap::isPortalsEntrance(lastOppositeDirection))
		{
			hadCollision = true;

			lastOppositeDirection -= oppositeMovementDirection;

			if (oppositeMovementDirection.Y() == 0)
			{
				oppositeMovementDirection = MoveDown;

				if (lastOppositeDirection.sqrDistance({ lastOppositeDirection.X(), startMovePosition.Y() })
					>= lastOppositeDirection.sqrDistance({ lastOppositeDirection.X(), endMovePosition.Y() }))
				{
					oppositeMovementDirection = MoveUp;
				}
			}
			else// if (oppositeMovementDirection.X() == 0)
			{
				oppositeMovementDirection = MoveRight;

				if (lastOppositeDirection.sqrDistance({ startMovePosition.X(), lastOppositeDirection.Y() })
					>= lastOppositeDirection.sqrDistance({ endMovePosition.X(), lastOppositeDirection.Y() }))
				{
					oppositeMovementDirection = MoveLeft;
				}
			}
		}

		return hadCollision;
	};

	// POSITIONS THE "BODY" FOLLOWING THE OPPOSITE MOVEMENT DIRECTION
	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightGreen);
	for (short i = 0; i < BodyInitialAmount; i++)
	{
		// NOTE: Needs improvements. Does not check very specific cases.
		// CASE TEST: "BodyInitialAmount" = 150 and "head position" starting at 91,24.
		do
		{
			lastOppositeDirection += oppositeMovementDirection;
		} while (checkForOppositeCollision());

		body.push_back(BodyPiece(lastOppositeDirection, '#'));
		body.back().printBodyPiece();
		//keyForDebugCaseTest = _getch();
	}

	// POSITIONS THE "TAIL"
	do
	{
		lastOppositeDirection += oppositeMovementDirection;
	} while (checkForOppositeCollision());

	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightYellow);
	tail = BodyPiece(lastOppositeDirection, '$');
	tail.printBodyPiece();
}

void Snake::movesTheSnake()
{
	Point nextHeadPosition = head.getPosition() + movementDirection;
	Point lastPosition = head.getPosition();
	Point lastTailPosition = tail.getPosition();

	bool hadGridMapCollision = false;
	bool hadBodyCollision = false;
	bool gotSomeFood = false;

	checkCollisions(nextHeadPosition, hadGridMapCollision, hadBodyCollision, gotSomeFood);

	if (gotSomeFood)
	{
		refUi.addScorePoints(Food::PointsPerFood);
		Timer::setTimerAndCallback(refUi.getSpeedPanelValue(), this, &Snake::movesTheSnake_callBack);
		Food::deleteFoodOnGridMap(nextHeadPosition);
	}

	// PREPARES TELETRANSPORT ACTION
	if (nextHeadPosition == GridMap::getUpperPortalPosition())
		head.setPosition(GridMap::getLowerPortalPosition());
	else if (nextHeadPosition == GridMap::getLowerPortalPosition())
		head.setPosition(GridMap::getUpperPortalPosition());

	// PERFORMS THE MOVEMENT
	head.addToPosition(movementDirection);
	lastMovementDirection = movementDirection;
	processesInputs();

	if (!body.empty())
	{
		Point lastPiecePosition = body.back().getPosition();
		body.push_front(body.back());
		body.front().setPosition(lastPosition);
		
		if (!gotSomeFood)
			body.pop_back();
		
		lastPosition = lastPiecePosition;
	}
	else if (gotSomeFood)
	{
		body.push_back(BodyPiece(lastPosition, '#'));
	}

	if (!gotSomeFood)
	{
		tail.setPosition(lastPosition);
		lastPosition = lastTailPosition;
	}

	printTheBodyWhenMoving(lastPosition, hadGridMapCollision, hadBodyCollision, gotSomeFood);
}

void Snake::checkCollisions(Point& refNextHeadPos, bool& refGridMapCollisionFlag,
	bool& refBodyCollisionFlag, bool& refGotFoodFlag)
{
	const char cursorPositionData = Game::getCursorPositionData(refNextHeadPos);

	// CHECK COLLISIONS WITH THE BODY ITSELF
	// NOTE: Does not consider the tail because it changes position in the same frame.
	if (!body.empty() && cursorPositionData == body.front().getBodySymbol())
	{
		refBodyCollisionFlag = isGameOver = true;
	}
	// CHECK COLLISIONS WITH GRID MAP BOUNDARIES
	else if (cursorPositionData == Stage::BorderCharacter)
	{
		refGridMapCollisionFlag = isGameOver = true;
	}

	// CHECK COLLISIONS WITH FOOD
	refGotFoodFlag = (cursorPositionData == Food::FoodCharacter);
}

void Snake::printTheBodyWhenMoving(const Point& refLastPosition, const bool& refGridMapCollisionFlag,
	const bool& refBodyCollisionFlag, const bool& refGotFoodFlag)
{
	if (!isGameOver)
	{
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightAqua);
		head.printBodyPiece();
	}

	if (!body.empty())
	{
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightGreen);
		body.front().printBodyPiece();

		if (refGotFoodFlag)
		{
			Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
			body.back().printBodyPiece();
		}
	}

	if (!refGotFoodFlag)
	{
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightYellow);
		tail.printBodyPiece();

		if (head.getPosition() != refLastPosition)
		{
			Game::setCursorPosition(refLastPosition);
			cout << ' ';
		}
	}

	if (isGameOver)
	{
		Timer::markTimerForDeletion(this, &Snake::movesTheSnake_callBack);

		if (refGridMapCollisionFlag)
			Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightRed);
		else if (refBodyCollisionFlag)
			Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightRed);

		head.printBodyPiece();
	}
}

void Snake::movesTheSnake_callBack(void* ownerObject)
{
	reinterpret_cast<Snake*>(ownerObject)->movesTheSnake();
}

void Snake::processesInputs_callBack(void* ownerObject)
{
	reinterpret_cast<Snake*>(ownerObject)->processesInputs();
}
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
#include "../Headers/Game.h"
#include "../Headers/GridMap.h"

using std::cout;
using std::endl;
//using std::string;

Point Snake::movementDirection;
BodyPiece Snake::head;
vector<BodyPiece> Snake::body;
BodyPiece Snake::tail;
bool Snake::isGameOver;

Snake::Snake()
	: MoveUp({ 0, -1 }), MoveDown({ 0, 1 }), MoveLeft({ -2, 0 }), MoveRight({ 2, 0 }), BodyInitialAmount(7)
{
	isGameOver = false;
}

void Snake::setupMovementBoundaries()
{
	startMovePosition = Game::StartScreenPoint; //3,1
	endMovePosition = Game::EndScreenPoint; //111,32

	// ADJUSTS FOR KEEP MOVEMENT INSIDE GRID LIMITS
	startMovePosition += {16, 8}; //19,9
	endMovePosition -= {16, 7}; //95,25

	createSnake();
	Game::setCursorPosition(25,13);
	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
	cout << '¶';
	Game::setCursorPosition(17,13);
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightRed);
	cout << '@';
}

bool Snake::runsGameplay()
{
    short key = 0;

	Timer::setTimerAndCallback(1200, &Snake::movesTheSnake);

    while (key != static_cast<short>(KeyValues::Enter) && !isGameOver)
    {
        Timer::run();

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
                    if (movementDirection != MoveDown) movementDirection = MoveUp;
                    break;

                case 'a':
                case 'A':
                case static_cast<short>(KeyValues::ArrowLeft):
					if (movementDirection != MoveRight) movementDirection = MoveLeft;
                    break;

                case 'd':
                case 'D':
                case static_cast<short>(KeyValues::ArrowRight):
					if (movementDirection != MoveLeft) movementDirection = MoveRight;
                    break;

                case 's':
                case 'S':
                case static_cast<short>(KeyValues::ArrowDown):
					if (movementDirection != MoveUp) movementDirection = MoveDown;
                    break;

                default:
                    break;
            }
        }
    }

	Timer::deleteTimer(&Snake::movesTheSnake);

	return false;
}

void Snake::createSnake()
{
	// RANDOMLY POSITION THE "HEAD" ON THE MAP
	const short xCoordLimit = static_cast<short>((endMovePosition.X() - startMovePosition.X()) * 0.5) + 1;
	const short yCoordLimit = static_cast<short>(endMovePosition.Y() - startMovePosition.Y() + 1);
	
	short randomXcoord, randomYcoord;

	randomXcoord = (rand() % xCoordLimit); // Seed has already been generated with srand in the Game constructor.
	randomYcoord = (rand() % yCoordLimit);

	head.setPosition(startMovePosition + Point(randomXcoord * 2, randomYcoord));

	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightAqua);
	head = BodyPiece(startMovePosition + Point(randomXcoord * 2, randomYcoord), '@');
	head.printBodyPiece();

	// DETERMINE THE DIRECTION OF THE SNAKE'S MOVEMENT
	Point centerPosition = {
		static_cast<int>((startMovePosition.X() + endMovePosition.X()) * 0.5),
		static_cast<int>((startMovePosition.Y() + endMovePosition.Y()) * 0.5) };

	movementDirection = centerPosition - head.getPosition();

	if (abs(movementDirection.X()) > abs(movementDirection.Y())) movementDirection = { (movementDirection.X() / abs(movementDirection.X())) * 2, 0 };
	else if (abs(movementDirection.Y()) > abs(movementDirection.X())) movementDirection = { 0, movementDirection.Y() / abs(movementDirection.Y()) };
	else
	{
		// Choose direction in "x" or "y" randomly.
		if (((rand() % 100) % 2) == 0) movementDirection = { (movementDirection.X() / abs(movementDirection.X())) * 2, 0 };
		else movementDirection = { 0, movementDirection.Y() / abs(movementDirection.Y()) };
	}

	// POSITIONS THE "BODY" FOLLOWING THE OPPOSITE MOVEMENT DIRECTION
	Point oppositeMovementDirection = movementDirection * -1;
	Point lastOppositeDirection = head.getPosition();
	
	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightGreen);
	for (short i = 0; i < BodyInitialAmount; i++)
	{
		lastOppositeDirection += oppositeMovementDirection; // criar swap no Point
		body.push_back(BodyPiece(lastOppositeDirection, '#'));
		body.back().printBodyPiece();
	}
	
	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightYellow);
	tail = BodyPiece(lastOppositeDirection, '$');
	tail.printBodyPiece();
}

void Snake::movesTheSnake()
{
	Point nextHeadPosition = head.getPosition() + movementDirection;

	// CHECK COLLISIONS WITH GRID MAP BOUNDARIES
	if (Game::getCursorPositionData(nextHeadPosition) == GridMap::BorderCharacter)
	{
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightRed);
		isGameOver = true;
	}
	
	// CHECK COLLISIONS WITH THE BODY ITSELF
	if (Game::getCursorPositionData(nextHeadPosition) == body.front().getBodySymbol() ||
		Game::getCursorPositionData(nextHeadPosition) == tail.getBodySymbol())
	{
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightRed);
		isGameOver = true;
	}

	// PERFORMS TELETRANSPORT ACTION
	if (nextHeadPosition == GridMap::getUpperPortalPosition()) head.setPosition(GridMap::getLowerPortalPosition());
	else if (nextHeadPosition == GridMap::getLowerPortalPosition()) head.setPosition(GridMap::getUpperPortalPosition());

	// PERFORM THE MOVEMENT
	head.addToPosition(movementDirection);

	if (isGameOver)
	{
		Timer::deleteTimer(&Snake::movesTheSnake);
	}
	else
	{
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::LightAqua);
	}

	head.printBodyPiece();
	if (isGameOver) Sleep(5000);
}
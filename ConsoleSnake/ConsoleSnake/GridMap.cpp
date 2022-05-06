/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Source file for drawing the boundaries of the arena and gameplay space.
 */

#include <iostream>
#include <iomanip>
#include "../Headers/GridMap.h"
#include "../Headers/Timer.h"
#include "../Headers/Stage.h"
#include "../Headers/Game.h"
#include "../Headers/Food.h"

using std::cout;
using std::endl;
using std::string;
using std::setfill;

Point GridMap::startMovePosition;
Point GridMap::endMovePosition;
Point GridMap::upperPortalPosition;
Point GridMap::lowerPortalPosition;

const int bordCol = 5; // ToDo Excluir após substituição

GridMap::GridMap(UI& ref)
{
	snake = new Snake(ref);
}

GridMap::~GridMap()
{
	delete snake;
	//delete startMovePosition;
	//delete endMovePosition;
	snake = NULL;
	//startMovePosition = NULL;
	//endMovePosition = NULL;
}

void GridMap::drawGrid()
{
	Point currentDrawPoint(Game::StartScreenPoint); //3,1
	Point endDrawPoint(Game::EndScreenPoint); //111,32
	
	// ADJUSTS FOR THE GRID LIMITS
	currentDrawPoint += {13, 7}; //16,8
	endDrawPoint -= {13, 6}; //98,26

	// PREPARES UPPER AND LOWER "PortalsPositions" FOR FURTHER RANDOM POSITIONING
	upperPortalPosition = currentDrawPoint;
	lowerPortalPosition = endDrawPoint;
	lowerPortalPosition -= {6, 0};

	// SETS GRIDMAP COLOR
	ConsoleColor borderColor = static_cast<ConsoleColor>(bordCol);
	Game::setTextColors(borderColor, borderColor);

	// DRAWS THE ARENA EDGES
	Game::setCursorPosition(currentDrawPoint); // 16,8
	short setW = endDrawPoint.X() - currentDrawPoint.X();
	cout << Stage::BorderCharacter << setfill(Stage::BorderCharacter) << std::setw(setW) << Stage::BorderCharacter;

	currentDrawPoint += {0, 1}; // 16,9

	while (currentDrawPoint.Y() < endDrawPoint.Y())
	{
		Game::setCursorPosition(currentDrawPoint);
		cout << std::setw(2) << Stage::BorderCharacter; // "setfill" is BorderCharacter
		Game::setCursorPosition(endDrawPoint.X() - 1, currentDrawPoint.Y());
		cout << std::setw(2) << Stage::BorderCharacter;
		currentDrawPoint += {0, 1};
	}

	Game::setCursorPosition(currentDrawPoint); // 16,26
	cout << Stage::BorderCharacter << setfill(Stage::BorderCharacter) << std::setw(setW) << Stage::BorderCharacter;

	// DRAWS THE PORTALS IN RANDOM POSITIONS
	drawPortals();
}

int GridMap::run()
{
	bool keepPlaying = true;

	if (snake != NULL)
	{
		snake->setupMovementBoundaries(startMovePosition, endMovePosition);

		Food::startFoodSpawner(startMovePosition, endMovePosition);

		while (keepPlaying)
		{
			Timer::run();
			keepPlaying = snake->processesGameplay();
		}

		showGameOver();
		Food::stopFoodSpawner();
		Timer::clearAll();
	}

	return BACKTOSTART;
}

bool GridMap::isPortalsEntrance(const Point& pointToCheck)
{
	Point upperEntrance = upperPortalPosition + Point(0, 1);
	Point lowerEntrance = lowerPortalPosition - Point(0, 1);

	return (upperEntrance == pointToCheck || lowerEntrance == pointToCheck);
}

Point GridMap::getUpperPortalPosition() { return upperPortalPosition; }
Point GridMap::getLowerPortalPosition() { return lowerPortalPosition; }
Point GridMap::getStartMovePosition() { return startMovePosition; }
Point GridMap::getEndMovePosition() { return endMovePosition; }

void GridMap::drawPortals()
{
	// RANDOMLY POSITIONS THE PORTALS
	const short xCoordLimit = static_cast<short>((lowerPortalPosition.X() - upperPortalPosition.X()) * 0.5) + 1;
	short randomXcoord = 0;

	randomXcoord = (rand() % xCoordLimit); // Seed has already been generated with srand in the Game constructor.
	upperPortalPosition += {randomXcoord * 2, 0};
	randomXcoord = (rand() % xCoordLimit);
	lowerPortalPosition -= {randomXcoord * 2, 0};

	auto printHalfPortal = [](const Point& position) // Lambda expression to draw half portal.
	{
		Game::setCursorPosition(position);
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Purple);
		cout << std::setw(2) << Stage::BorderCharacter; // "setfill" is BorderCharacter.
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Purple);
		cout << "   ";
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Purple);
		cout << std::setw(2) << Stage::BorderCharacter;
	};

	printHalfPortal(upperPortalPosition);// ?, 8
	upperPortalPosition -= { 0, 1 };
	printHalfPortal(upperPortalPosition);// ?, 7

	printHalfPortal(lowerPortalPosition); // ?, 26
	lowerPortalPosition += { 0, 1 };
	printHalfPortal(lowerPortalPosition); // ?, 27

	// PREPARES THE PORTALS ENTRY POSITIONS FOR GAMEPLAY
	upperPortalPosition += { 3, 0 };
	lowerPortalPosition += { 3, 0 };
}

void GridMap::showGameOver()
{
	string gameOver = " | FIM DE JOGO | ";
	short setW = static_cast<short>(gameOver.length() - 2);
	short halfGameOVerLength = static_cast<short>(gameOver.length() * 0.5);

	Point centerPosition = {
		static_cast<int>((startMovePosition.X() + endMovePosition.X()) * 0.5),
		static_cast<int>((startMovePosition.Y() + endMovePosition.Y()) * 0.5) };
	
	Point upperPosition = centerPosition - Point{ halfGameOVerLength, 1 };

	Sleep(1000);

	Game::backToTitleScreenColors();

	Game::setCursorPosition(upperPosition);
	cout << " +" << std::setfill('-') << std::setw(setW) << "+ ";
	upperPosition += { 0, 1 };

	Game::setCursorPosition(upperPosition);
	cout << gameOver;
	upperPosition += { 0, 1 };

	Game::setCursorPosition(upperPosition);
	cout << " +" << std::setfill('-') << std::setw(setW) << "+ ";

	Sleep(2500);
}
/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Source file for drawing the boundaries of the arena and gameplay space.
 */

#include <iostream>
#include <iomanip>
#include "../Headers/GridMap.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
using std::string;
using std::setfill;

Point GridMap::upperPortalPosition;
Point GridMap::lowerPortalPosition;
const char GridMap::BorderCharacter = '|';

const int bordCol = 5; // ToDo Excluir após substituição

GridMap::GridMap()
{
}


void GridMap::drawGrid()
{
	Point currentDrawPoint(Game::StartScreenPoint); //3,1
	Point endDrawPoint(Game::EndScreenPoint); //111,32
	
	// ADJUSTS FOR GRID LIMITS
	currentDrawPoint += {13, 7}; //16,8
	endDrawPoint -= {13, 6}; //98,26

	// PREPARE UPPER AND LOWER "PortalsPosition" FOR FURTHER RANDOM POSITIONING
	upperPortalPosition = currentDrawPoint;
	lowerPortalPosition = endDrawPoint;
	lowerPortalPosition += {-6, 0};

	// SETS GRIDMAP COLOR
	ConsoleColor borderColor = static_cast<ConsoleColor>(bordCol);
	Game::setTextColors(borderColor, borderColor);

	// DRAW THE ARENA EDGES
	Game::setCursorPosition(currentDrawPoint); // 16,8
	short setW = endDrawPoint.X() - currentDrawPoint.X();
	cout << BorderCharacter << setfill(BorderCharacter) << std::setw(setW) << BorderCharacter;

	currentDrawPoint += {0, 1}; // 16,9

	while (currentDrawPoint.Y() < endDrawPoint.Y())
	{
		Game::setCursorPosition(currentDrawPoint);
		cout << std::setw(2) << BorderCharacter; // "setfill" is BorderCharacter
		Game::setCursorPosition(endDrawPoint.X() - 1, currentDrawPoint.Y());
		cout << std::setw(2) << BorderCharacter;
		currentDrawPoint += {0, 1};
	}

	Game::setCursorPosition(currentDrawPoint); // 16,26
	cout << BorderCharacter << setfill(BorderCharacter) << std::setw(setW) << BorderCharacter;

	// DRAW THE PORTALS IN RANDOM POSITIONS
	drawPortals();
}

bool GridMap::isPortalsEntrance(const Point& pointToCheck)
{
	Point upperEntrance = upperPortalPosition + Point(0, 1);
	Point lowerEntrance = lowerPortalPosition - Point(0, 1);

	return (upperEntrance == pointToCheck || lowerEntrance == pointToCheck);
}

Point GridMap::getUpperPortalPosition() { return upperPortalPosition; }

Point GridMap::getLowerPortalPosition() { return lowerPortalPosition; }

void GridMap::drawPortals()
{
	// RANDOMLY POSITION THE PORTALS
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
		cout << std::setw(2) << BorderCharacter; // "setfill" is BorderCharacter.
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Purple);
		cout << "   ";
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Purple);
		cout << std::setw(2) << BorderCharacter;
	};

	printHalfPortal(upperPortalPosition);// ?, 8
	upperPortalPosition -= { 0, 1 };
	printHalfPortal(upperPortalPosition);// ?, 7

	printHalfPortal(lowerPortalPosition); // ?, 26
	lowerPortalPosition += { 0, 1 };
	printHalfPortal(lowerPortalPosition); // ?, 27

	// PREPARE PORTALS ENTRY POSITIONS FOR GAMEPLAY
	upperPortalPosition += { 3, 0 };
	lowerPortalPosition += { 3, 0 };
}
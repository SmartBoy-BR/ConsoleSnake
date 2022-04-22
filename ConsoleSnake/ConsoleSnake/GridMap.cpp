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
	upperPortalPosition -= {0, 1};
	lowerPortalPosition = endDrawPoint;
	lowerPortalPosition += {-6, 1};

	// DRAW THE ARENA EDGES
	Game::setCursorPosition(currentDrawPoint); // 16,8
	short setW = endDrawPoint.X() - currentDrawPoint.X();
	cout << '|' << std::setfill('|') << std::setw(setW) << '|';

	currentDrawPoint += {0, 1}; // 16,9

	while (currentDrawPoint.Y() < endDrawPoint.Y())
	{
		Game::setCursorPosition(currentDrawPoint);
		cout << "||";
		Game::setCursorPosition(endDrawPoint.X() - 1, currentDrawPoint.Y());
		cout << "||";
		currentDrawPoint += {0, 1};
	}

	Game::setCursorPosition(currentDrawPoint); // 16,26
	cout << '|' << std::setfill('|') << std::setw(setW) << '|';

	// DRAW THE PORTALS IN RANDOM POSITIONS
	drawPortals();
}

void GridMap::drawPortals()
{
	const string halfPortal = "||   ||";
	const short xCoordLimit = static_cast<short>((lowerPortalPosition.X() - upperPortalPosition.X()) * 0.5) + 1;
	short randomXcoord;

	randomXcoord = (rand() % xCoordLimit); // Seed has already been generated with srand in the Game constructor.
	upperPortalPosition += {randomXcoord * 2, 0};
	randomXcoord = (rand() % xCoordLimit);
	lowerPortalPosition -= {randomXcoord * 2, 0};

	Game::setCursorPosition(upperPortalPosition); // ?, 7
	cout << halfPortal;
	upperPortalPosition += { 0, 1 };
	Game::setCursorPosition(upperPortalPosition); // ?, 8
	cout << halfPortal;

	Game::setCursorPosition(lowerPortalPosition); // ?, 27
	cout << halfPortal;
	lowerPortalPosition -= { 0, 1 };
	Game::setCursorPosition(lowerPortalPosition); // ?, 26
	cout << halfPortal;

	// PREPARE THE POSITIONS OF THE PORTALS FOR GAMEPLAY
	upperPortalPosition += { 3, 0 };
	lowerPortalPosition += { 3, 0 };
}
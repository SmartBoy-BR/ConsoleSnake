/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level source file with implementations of global gameplay pre-management systems.
 */

#include <conio.h>
#include <iostream>
#include <iomanip>
#include "../Headers/Stage.h"
#include "../Headers/Timer.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
using std::string;

Stage::Stage()
{
	playStates = PlayStates::Playing;
}

Stage::~Stage()
{
}

int Stage::run()
{
	drawStageScreen();
	ui.setupUI();
	gridMap.drawGrid();
	snake.setupMoveBoundaries();

	return BACKTOSTART;
}

void Stage::drawStageScreen()
{
	Point currentDrawPoint(Game::StartScreenPoint); //3,1
	Point endDrawPoint(Game::EndScreenPoint); //111,32

	// ADJUST TO CENTER COORDINATES
	currentDrawPoint += {6, 1};
	endDrawPoint -= {6, 3};

	// DRAW THE STAGE BOUNDARIES
	Game::setCursorPosition(currentDrawPoint); //9,2
	cout << "CONSOLE SNAKE v1.0";
	currentDrawPoint += {0, 1};
	Game::setCursorPosition(currentDrawPoint); // 9,3
	short setW = endDrawPoint.X() - currentDrawPoint.X();
	cout << '+' << std::setfill('-') << std::setw(setW) << '+';

	currentDrawPoint += {0, 1}; // 9,4

	while (currentDrawPoint.Y() < endDrawPoint.Y())
	{
		Game::setCursorPosition(currentDrawPoint);
		cout << '|' << std::setfill(' ') << std::setw(setW) << '|';
		currentDrawPoint += {0, 1};
	}

	Game::setCursorPosition(currentDrawPoint); // 9,29
	cout << '+' << std::setfill('-') << std::setw(setW) << '+';
}
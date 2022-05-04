/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level source file with implementations of global gameplay pre-management systems.
 */

#include <conio.h>
#include <iostream>
#include <iomanip>
#include "../Headers/Stage.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
using std::string;

const char Stage::BorderCharacter = '|';

Stage::Stage()
{
	gridMap = NULL;
	playStates = PlayStates::Playing;
}

Stage::~Stage()
{
	delete gridMap;
	gridMap = NULL;
}

int Stage::run()
{
	drawStageScreen();
	ui.setupUI();

	gridMap = new GridMap(ui);

	if (gridMap != NULL)
	{
		gridMap->drawGrid();
		gridMap->run();
	}

	return BACKTOSTART;
}

void Stage::drawStageScreen()
{
	Point currentDrawPoint(Game::StartScreenPoint); //3,1
	Point endDrawPoint(Game::EndScreenPoint); //111,32

	// ADJUSTS TO THE STAGE BOUNDARIES
	currentDrawPoint += {6, 1};
	endDrawPoint -= {6, 3};

	Game::setCursorPosition(currentDrawPoint); //9,2
	cout << "CONSOLE SNAKE v1.0";

	// SETS STAGE COLOR
	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Purple);

	// DRAWS THE STAGE BOUNDARIES
	currentDrawPoint += {0, 1};
	Game::setCursorPosition(currentDrawPoint); // 9,3
	short setW = endDrawPoint.X() - currentDrawPoint.X();
	cout << '+' << std::setfill('-') << std::setw(setW) << '+';

	currentDrawPoint += {0, 1}; // 9,4

	while (currentDrawPoint.Y() < endDrawPoint.Y())
	{
		Game::setCursorPosition(currentDrawPoint);
		cout << BorderCharacter << std::setfill(' ') << std::setw(setW) << BorderCharacter;
		currentDrawPoint += {0, 1};
	}

	Game::setCursorPosition(currentDrawPoint); // 9,29
	cout << '+' << std::setfill('-') << std::setw(setW) << '+';
}
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

Stage::Stage(Game* ptrGame)
	: ptrGame(ptrGame)
{
}

Stage::~Stage()
{
	ptrGame = NULL;
}

int Stage::run()
{
	if (ptrGame == NULL)
	{
		cout << "Não foi possível preparar a stageScreen por falta da referência \"game\"." << endl;
		return ERROR;
	}

	drawStageScreen();

	return BACKTOSTART;
}

void Stage::drawStageScreen()
{
	cout << "Back to start in 1.5 secs..." << endl;
	Sleep(1500);
}
/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level header with global gameplay system settings.
 */

#pragma once

class Game;

#include "../Headers/Point.h"

enum class PlayStates { Playing, GameOver, BackToStart };

class Stage
{
	private:
		Game*		ptrGame;

		void drawStageScreen();
		//static void blinkGetReadyMsg();

	public:
		Stage(Game* ptrGame);
		~Stage();
		int run();
};
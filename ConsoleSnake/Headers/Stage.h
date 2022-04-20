/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level header with global gameplay system settings.
 */

#pragma once

#include "../Headers/Point.h"
#include "../Headers/UI.h"

enum class PlayStates { Playing, GameOver, BackToStart };

class Stage
{
	private:
		UI			ui;
		PlayStates	playStates;

		void drawStageScreen();
		//static void blinkGetReadyMsg();

	public:
		Stage();
		~Stage();
		int run();
};
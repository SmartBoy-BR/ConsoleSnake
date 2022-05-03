/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level header with global gameplay system settings.
 */

#pragma once

#include "../Headers/Point.h"
#include "../Headers/UI.h"
#include "../Headers/GridMap.h"

enum class PlayStates { Playing, GameOver, BackToStart };

class Stage
{
	private:
		UI				ui;
		GridMap*		gridMap;
		PlayStates		playStates;
		static short	localHexaColorsCode;

		void drawStageScreen();

	public:
		static const char BorderCharacter;

		Stage(short hexaColorsCode);
		~Stage();
		int run();
		static short getHexaColorsCode();
};
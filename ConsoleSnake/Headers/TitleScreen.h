/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-18
 *
 * FUNCTION: Header with the settings to draw and wait for the user's choice on the home screen.
 */

#pragma once

class Game;

#include <vector>
#include <Windows.h>
#include "../Headers/Point.h"

class TitleScreen
{
	private:
		Game*						ptrGame;
		Point						playerChoiceArrow;
		static bool					enableEnterMessage;
		static Point				blinkMsgPosition;
		static std::vector<short>   TitleScreenBackColors;
		static short                numberLimit;
		static short                lastRandom;

		void drawTitleScreen();
		static void blinkPressEnterMsg();
		static void changeTitleScreenColors();

	public:
		TitleScreen(Game* ptrGame);
		~TitleScreen();
		int prepareTitleScreen();
		bool waitingForPlayerChoice();
};
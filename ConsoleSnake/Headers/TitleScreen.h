/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-18
 *
 * FUNCTION: Header with the settings to draw and wait for the user's choice on the home screen.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"

class TitleScreen
{
	private:
		static Point				playerChoiceArrow;
		static bool					enableEnterMessage;
		static bool					enableChoiceArrow;
		static Point				blinkMsgPosition;
		static std::vector<short>   TitleScreenBackColors;
		static short                numberLimit;
		static short                lastRandom;

		void drawTitleScreen();
		static void blinkPressEnterMsg();
		static void blinkChoiceArrow();
		static void changeTitleScreenColors();

	public:
		TitleScreen();
		~TitleScreen();
		int prepareTitleScreen();
		bool waitingForPlayerChoice();
};
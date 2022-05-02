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
		Point				playerChoiceArrow;
		bool				showEnterMessage;
		bool				showChoiceArrow;
		Point				blinkMsgPosition;
		std::vector<short>	titleScreenBackColors;
		short				numberLimit;
		short				lastRandom;

		static void blinkPressEnterMsg_callBack(void* ownerObject);
		static void blinkChoiceArrow_callBack(void* ownerObject);
		static void changeTitleScreenColors_callBack(void* ownerObject);

		void drawTitleScreen();
		void blinkPressEnterMsg();
		void blinkChoiceArrow();
		void changeTitleScreenColors();
		void setsTitleScreenColors();

	public:
		TitleScreen();
		~TitleScreen();
		int prepareTitleScreen();
		bool waitingForPlayerChoice();
};
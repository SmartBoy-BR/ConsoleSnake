/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-20
 *
 * FUNCTION: Header with user interface settings.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"

class UI
{
	private:
		static bool						showScorePoints;
		static bool						showHiScorePoints;
		static bool						showSpeedValue;
		static Point					scorePanelPosition;
		static Point					hiScorePanelPosition;
		static Point					snakeSpeedPanelPosition;
		static unsigned short			scorePanelPoints;
		static unsigned short			pointsToAdd;
		static unsigned short			hiScorePanelPoints;
		static unsigned short			snakeSpeedPanelValue;
		static unsigned short			speedToDecrement;
		static std::vector<void (*)()>	blinkMethods;


		void drawUI();
		static void blinkScore();
		static void blinkHiScore();
		static void blinkSpeedValue();
		static void writeScore();
		static void writeHiScore();
		static void writeSpeedValue();
		static void prepareToStopBlinking();
		static void stopBlinking();

	public:
		UI();
		void setupUI();
		static void addScorePoints(unsigned short morePoints);
		static unsigned short getSpeedPanelValue();
		static void deleteUItimers();
};
/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-20
 *
 * FUNCTION: Header with user interface settings.
 */

#pragma once

#include "../Headers/Point.h"

class UI
{
	private:
		static Point			scorePanelPosition;
		static Point			hiScorePanelPosition;
		static Point			snakeSpeedPanelPosition;
		static unsigned short	scorePanelPoints;
		static unsigned short	hiScorePanelPoints;
		static unsigned short	snakeSpeedPanelValue;

		void drawUI();
		void addScorePoints(unsigned short morePoints);
		void updateHiScorePoints();
		void updateSnakeSpeedValue(unsigned short newSpeed);

	public:
		UI();
		void setupUI();
};
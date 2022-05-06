/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-20
 *
 * FUNCTION: Header with user interface settings.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"

using std::vector;

class UI
{
	private:
		const short				PointsToIncreaseSpeed;
		const short				StartTimeSpeed;
		bool					showScorePoints;
		bool					showHiScorePoints;
		bool					showSpeedValue;
		Point					scorePanelPosition;
		Point					hiScorePanelPosition;
		Point					snakeSpeedPanelPosition;
		unsigned short			scorePanelPoints;
		unsigned short			pointsToAdd;
		unsigned short			hiScorePanelPoints;
		unsigned short			snakeSpeedPanelValue;
		unsigned short			nextSnakeSpeedValue;
		vector<void (*)(void*)>	blinkMethods;

		static void blinkScore_callBack(void* ownerObject);
		static void blinkHiScore_callBack(void* ownerObject);
		static void blinkSpeedValue_callBack(void* ownerObject);
		static void prepareToStopBlinking_callBack(void* ownerObject);
		static void stopBlinking_callBack(void* ownerObject);

		void setNextSpeedPanelValue();
		void drawUI();
		void blinkScore();
		void blinkHiScore();
		void blinkSpeedValue();
		void writeScore();
		void writeHiScore();
		void writeSpeedValue();
		void prepareToStopBlinking();
		void stopBlinking();

	public:
		const short	MinimumTimeSpeed;

		UI();
		void setupUI();
		void addScorePoints(unsigned short morePoints);
		unsigned short getNextSpeedPanelValue();
		void deleteUItimers();
};
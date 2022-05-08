/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-20
 *
 * FUNCTION: Header with user interface settings.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"

enum class ConsoleColor;

using std::vector;

typedef unsigned short ushort;
typedef unsigned char uchar;

class UI
{
	private:
		static const vector<ushort>	SnakeSpeedTimes;
		const ConsoleColor			BackgroundColor;
		const ConsoleColor			ScoreForegroundColor;
		const ConsoleColor			HiScoreForegroundColor;
		const ConsoleColor			SpeedForegroundColor;
		const short					PointsToIncreaseSpeed;
		bool						showScorePoints;
		bool						showHiScorePoints;
		bool						showSpeedValue;
		Point						scorePanelPosition;
		Point						hiScorePanelPosition;
		Point						snakeSpeedPanelPosition;
		ushort						scorePanelPoints;
		ushort						nextScoreValue;
		ushort						hiScorePanelPoints;
		ushort						snakeSpeedPanelValue;
		ushort						speedTimeIndex;
		ushort						nextSnakeSpeedTime;
		vector<void (*)(void*)>		blinkMethods;

		static void blinkScore_callBack(void* ownerObject);
		static void blinkHiScore_callBack(void* ownerObject);
		static void blinkSpeedValue_callBack(void* ownerObject);
		static void prepareToStopBlinking_callBack(void* ownerObject);
		static void stopBlinking_callBack(void* ownerObject);

		void drawUI();
		void blinkPanelValue(bool& showPanelValue, const ConsoleColor& valueForegroundColor);
		void writePanelValue(const Point& panelPosition, const uchar setW, const ushort& panelValue);
		void writeAllPanelValues();
		void prepareToStopBlinking();
		void stopBlinking();

	public:
		UI();
		void setupUI();
		void addScorePoints(ushort pointsToAdd);
		ushort getNextSpeedPanelValue();
		ushort getMinimumTimeSpeed();
		void deleteUItimers();
};
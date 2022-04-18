#pragma once
#include "../Headers/Point.h"

class Stage
{
	private:
		Stage();
		Point startPosition;
		Point endPosition;
		void drawStageScreen();

	public:
		Stage(Point startP, Point endP);
		void run();
};
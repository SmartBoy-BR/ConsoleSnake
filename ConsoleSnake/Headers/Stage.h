/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level header with global gameplay system settings.
 */

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
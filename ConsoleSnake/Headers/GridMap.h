/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to draw the boundaries and arena of gameplay.
 */

#pragma once

#include "../Headers/Snake.h"
#include "../Headers/Point.h"
#include "../Headers/Food.h"

class GridMap
{
	private:
		Snake*			snake;
		static Point	startMovePosition;
		static Point	endMovePosition;
		static Point	upperPortalPosition;
		static Point	lowerPortalPosition;

		void drawPortals();
		void showGameOver();

	public:
		GridMap(UI& ref);
		~GridMap();
		void drawGrid();
		int run();
		static bool isPortalsEntrance(const Point& pointToCheck);
		static Point getUpperPortalPosition();
		static Point getLowerPortalPosition();
		static Point getStartMovePosition();
		static Point getEndMovePosition();
};
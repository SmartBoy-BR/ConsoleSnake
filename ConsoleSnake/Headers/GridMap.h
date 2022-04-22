/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to draw the boundaries and arena of gameplay.
 */

#pragma once

#include "../Headers/Point.h"

class GridMap
{
	private:
		Point	upperPortalPosition;
		Point	lowerPortalPosition;

		void drawPortals();

	public:
		GridMap();
		void drawGrid();
};
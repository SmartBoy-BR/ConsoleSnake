/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to draw the boundaries and arena of gameplay.
 */

#pragma once

#include "../Headers/Point.h"
#include "../Headers/Food.h"

class GridMap
{
	private:
		static Point		upperPortalPosition;
		static Point		lowerPortalPosition;

		void drawPortals();

	public:
		static const char	BorderCharacter;

		GridMap();
		void drawGrid();
		static Point getUpperPortalPosition();
		static Point getLowerPortalPosition();
};
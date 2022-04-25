/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-23
 *
 * FUNCTION: Snake food definition header.
 */

#pragma once

#include "../Headers/Point.h"

class Food
{
	private:
		Point	gridPosition;

	public:
		static const char	FoodCharacter;

		Food();
};
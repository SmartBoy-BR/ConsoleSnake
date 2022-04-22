/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to configure all snake behavior.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"
#include "../Headers/BodyPiece.h"

class Snake
{
	private:
		Point					startMovePosition;
		Point					endMovePosition;
		Point					moveDirection;
		BodyPiece				head;
		std::vector<BodyPiece>	body;
		BodyPiece				tail;

	public:
		Snake();
		void setupMoveBoundaries();
		void moveSnake();
};
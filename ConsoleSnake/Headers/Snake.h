/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to configure all snake behavior.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"
#include "../Headers/BodyPiece.h"

using std::vector;

class Snake
{
	private:
		const Point					MoveUp;
		const Point					MoveDown;
		const Point					MoveLeft;
		const Point					MoveRight;
		const unsigned short		BodyInitialAmount;
		Point						startMovePosition;
		Point						endMovePosition;
		static Point				movementDirection;
		static BodyPiece			head;
		static vector<BodyPiece>	body;
		static BodyPiece			tail;
		static bool					isGameOver;

		void createSnake();
		static void movesTheSnake();

	public:
		Snake();
		void setupMovementBoundaries();
		bool runsGameplay();
};
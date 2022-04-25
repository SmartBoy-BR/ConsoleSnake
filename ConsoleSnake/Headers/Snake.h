/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to configure all snake behavior.
 */

#pragma once

#include <list>
#include "../Headers/Point.h"
#include "../Headers/BodyPiece.h"

using std::list;

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
		static Point				lastMovementDirection;
		static BodyPiece			head;
		static list<BodyPiece>		body;
		static BodyPiece			tail;
		static bool					isGameOver;

		void createSnakeHead();
		void createSnakeBody();
		static void movesTheSnake();

	public:
		Snake();
		void setupMovementBoundaries();
		bool runsGameplay();
};
/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to configure all snake behavior.
 */

#pragma once

#include <list>
#include "../Headers/Point.h"
#include "../Headers/BodyPiece.h"
#include "../Headers/UI.h"

using std::list;

class Snake
{
	private:
		UI&						refUi;
		const Point				MoveUp;
		const Point				MoveDown;
		const Point				MoveLeft;
		const Point				MoveRight;
		const unsigned char		BodyInitialAmount;

		Point				startMovePosition;
		Point				endMovePosition;
		Point				movementDirection;
		Point				lastMovementDirection;
		BodyPiece			head;
		list<BodyPiece>		body;
		BodyPiece			tail;
		bool				isGameOver;

		static void movesTheSnake_callBack(void* ownerObject);
		static void processesInputs_callBack(void* ownerObject);

		int processesInputs();
		void createSnakeHead();
		void createSnakeBody();
		void movesTheSnake();
		void checkCollisions(Point&, bool&, bool&, bool&);
		void printTheBodyWhenMoving(const Point&, const bool&, const bool&, const bool&);

	public:
		Snake(UI& ref);
		void setupMovementBoundaries(Point& refStartPosition, Point& refEndPosition);
		bool processesGameplay();
		Point getSnakeHeadPosition();
};
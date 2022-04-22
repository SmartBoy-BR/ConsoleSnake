/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Source file for drawing and managing player (snake) behavior.
 */

#include <iostream>
#include <iomanip>
#include "../Headers/Snake.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
//using std::string;

Snake::Snake()
	: head ({ 23, 13 }, '@'), tail({ 19, 15 }, '§')
{
	moveDirection = { 2, 0 };
	body.push_back(BodyPiece({ 21, 13 }, '#'));
	body.push_back(BodyPiece({ 19, 13 }, '#'));
	body.push_back(BodyPiece({ 19, 14 }, '#'));
}

void Snake::setupMoveBoundaries()
{
	startMovePosition = Game::StartScreenPoint; //3,1
	endMovePosition= Game::EndScreenPoint; //111,32

	// ADJUSTS FOR KEEP MOVEMENT INSIDE GRID LIMITS
	startMovePosition += {16, 8}; //19,9
	endMovePosition -= {16, 7}; //95,25

	//while (startMovePosition.X() <= endMovePosition.X())
	/*for (short i = (endMovePosition.X() - startMovePosition.X()) / 2; i >= 0; i--)
	{
		Game::setCursorPosition(startMovePosition);
		cout << "#";
		startMovePosition += moveDirection;

		Game::setCursorPosition(endMovePosition);
		cout << "@";
		endMovePosition -= moveDirection;
	}*/

	head.printBodyPiece();
	for (BodyPiece bodyPiece : body) bodyPiece.printBodyPiece();
	tail.printBodyPiece();

	Sleep(50000);
}

void Snake::moveSnake()
{
}
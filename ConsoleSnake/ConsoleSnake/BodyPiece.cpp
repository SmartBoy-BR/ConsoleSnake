/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Source file with the implementation of snake body parts definitions.
 */

#include <iostream>
#include <iomanip>
#include "../Headers/BodyPiece.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
//using std::string;

BodyPiece::BodyPiece(Point gridPos, char bodySymbol)
{
	gridPosition = gridPos;
	bodyConsoleSymbol = bodySymbol;
}

void BodyPiece::printBodyPiece()
{
	Game::setCursorPosition(gridPosition);
	cout << bodyConsoleSymbol;
}

Point BodyPiece::getPosition() { return gridPosition; }

void BodyPiece::setPosition(Point newPosition)
{
	gridPosition = newPosition;
}
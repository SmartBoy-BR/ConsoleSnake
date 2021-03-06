/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Source file with the implementation of snake body parts definitions.
 */

#include <iostream>
#include "../Headers/BodyPiece.h"
#include "../Headers/Game.h"

using std::cout;

BodyPiece::BodyPiece()
{
	bodyConsoleSymbol = '?';
}

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

char BodyPiece::getBodySymbol()
{
	return bodyConsoleSymbol;
}

Point BodyPiece::getPosition() { return gridPosition; }

void BodyPiece::setPosition(Point newPosition)
{
	gridPosition = newPosition;
}

void BodyPiece::addToPosition(Point pointToAdd)
{
	gridPosition += pointToAdd;
}
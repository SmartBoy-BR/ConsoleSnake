/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-21
 *
 * FUNCTION: Header to settings common snake body properties.
 */

#pragma once

#include "../Headers/Point.h"

class BodyPiece
{
	private:
		Point	gridPosition;
		char	bodyConsoleSymbol;

	public:
		BodyPiece();
		BodyPiece(Point gridPos, char bodySymbol);
		void printBodyPiece();
		char getBodySymbol();
		Point getPosition();
		void setPosition(Point newPosition);
		void addToPosition(Point pointToAdd);
};
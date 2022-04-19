/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level source file with implementations of global gameplay pre-management systems.
 */

#include "../Headers/Stage.h"
#include "../Headers/Timer.h"

Stage::Stage(Point startP, Point endP)
	: startPosition(startP), endPosition(endP)
{
}

void Stage::run()
{
	drawStageScreen();
}

void Stage::drawStageScreen()
{

}
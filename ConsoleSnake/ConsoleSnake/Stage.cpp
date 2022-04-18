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
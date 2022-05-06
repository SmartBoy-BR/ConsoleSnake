/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-23
 *
 * FUNCTION: Source file with snake food implementations.
 */

#include <iostream>
#include "../Headers/Food.h"
#include "../Headers/Timer.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;

std::vector<Food*> Food::foodsOnGridMap;
Point Food::startMovePosition;
Point Food::endMovePosition;
//Point Food::(Snake::* snakeHeadPosMethodPtr)();
const char Food::FoodCharacter = 'o';
const short Food::PointsPerFood = 100;

Food::Food(Point& spawnPos, unsigned char lifeTimeInSecs)
	: GridPosition(spawnPos), RemainingTimeToStartBlinking(3), MinSqrDistanceToSnakeHead(32)
{
	lifeTimeInSeconds = lifeTimeInSecs;
	showFoodOnGridMap = true;

	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
	writeFoodCharacter();

	Timer::setTimerAndCallback(1000, this, &decreaseLifeTime_callBack);
}

void Food::startFoodSpawner(Point& startPos, Point& endPos)
{
	startMovePosition = startPos;
	endMovePosition = endPos;
	Timer::setTimerAndCallback(((rand() % 3) + 2) * 1000, // 0 to 2 plus 2 => (2..4) * 1000
		NULL, &runFoodSpawner);
}

void Food::stopFoodSpawner() { Timer::markTimerForDeletion(NULL, &runFoodSpawner); }

void Food::deleteFoodOnGridMap(Point gridPosition)
{
	Food* foodPtr;

	for (size_t idx = foodsOnGridMap.size(); idx > 0; idx--)
	{
		foodPtr = foodsOnGridMap[idx - 1];

		if (gridPosition == foodPtr->GridPosition)
		{
			Timer::markTimerForDeletion(foodPtr, &blinkFoodOnGridMap_callBack);
			Timer::markTimerForDeletion(foodPtr, &decreaseLifeTime_callBack);

			Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
			Game::setCursorPosition(foodPtr->GridPosition);
			cout << ' ';

			delete foodPtr;
			foodsOnGridMap[idx - 1] = NULL;
			foodsOnGridMap.erase(foodsOnGridMap.begin() + idx - 1);
		}
	}
}

void Food::writeFoodCharacter()
{
	Game::setCursorPosition(GridPosition);
	cout << FoodCharacter;
}

void Food::decreaseLifeTime()
{
	if (--lifeTimeInSeconds == 0)
	{
		deleteFoodOnGridMap(GridPosition);
		return;
	}
	else if (lifeTimeInSeconds == RemainingTimeToStartBlinking)
	{
		Timer::setTimerAndCallback(100, this, &blinkFoodOnGridMap_callBack);
	}
}

void Food::blinkFoodOnGridMap()
{
	showFoodOnGridMap = !showFoodOnGridMap;

	if (showFoodOnGridMap)
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
	else
		Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Gray);

	writeFoodCharacter();
}

void Food::runFoodSpawner(void* nullObj)
{
	Point newFoodPosition;
	
	do
	{
		newFoodPosition = startMovePosition;

		const short xCoordLimit = static_cast<short>((endMovePosition.X() - startMovePosition.X()) * 0.5) + 1;
		const short yCoordLimit = static_cast<short>(endMovePosition.Y() - startMovePosition.Y() + 1);

		short randomXcoord, randomYcoord;

		randomXcoord = (rand() % xCoordLimit);
		randomYcoord = (rand() % yCoordLimit);

		newFoodPosition += { randomXcoord * 2, randomYcoord };
	
	} while (Game::getCursorPositionData(newFoodPosition) != ' ');

	foodsOnGridMap.push_back(new Food(newFoodPosition, (rand() % 6) + 7)); // 0 to 5 plus 7 => (7..12)
	Timer::setTimerAndCallback(((rand() % 7) + 2) * 1000, // 0 to 6 plus 2 => (2..8) * 1000
		NULL, &runFoodSpawner);
}

void Food::decreaseLifeTime_callBack(void* ownerObject)
{
	reinterpret_cast<Food*>(ownerObject)->decreaseLifeTime();
}

void Food::blinkFoodOnGridMap_callBack(void* ownerObject)
{
	reinterpret_cast<Food*>(ownerObject)->blinkFoodOnGridMap();
}
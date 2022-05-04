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
const char Food::FoodCharacter = 'o';
const short Food::PointsPerFood = 100;

Food::Food(Point& spawnPos, unsigned char lifeTimeInSecs)
	: GridPosition(spawnPos), RemainingTimeToStartBlinking(3)
{
	lifeTimeInSeconds = lifeTimeInSecs;
	showFoodOnGridMap = true;

	Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Yellow);
	writeFoodCharacter();

	Timer::setTimerAndCallback(1000, this, &decreaseLifeTime_callBack);
}

void Food::startFoodSpawner()
{


	foodsOnGridMap.push_back(new Food(Point{ 19, 9 }, 10));
	foodsOnGridMap.push_back(new Food(Point{ 23, 13 }, 7));
}

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

void Food::decreaseLifeTime_callBack(void* ownerObject)
{
	reinterpret_cast<Food*>(ownerObject)->decreaseLifeTime();
}

void Food::blinkFoodOnGridMap_callBack(void* ownerObject)
{
	reinterpret_cast<Food*>(ownerObject)->blinkFoodOnGridMap();
}
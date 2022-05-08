/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-23
 *
 * FUNCTION: Source file with snake food implementations.
 */

#include <iostream>
#include "../Headers/Food.h"
#include "../Headers/Timer.h"
#include "../Headers/Game.h"
#include "../Headers/GridMap.h"
#include "../Headers/Stage.h"

using std::cout;

const ConsoleColor Food::BackgroundColor = Stage::BackgroundColor;
const ConsoleColor Food::ForegroundColor = ConsoleColor::Yellow;
const unsigned char Food::TriesAmount = 5;
std::vector<Food*> Food::foodsOnGridMap;
Point Food::startMovePosition;
Point Food::endMovePosition;
const char Food::FoodCharacter = 'o';
const short Food::PointsPerFood = 100;

Food::Food(Point& spawnPos, unsigned char lifeTimeInSecs)
	: GridPosition(spawnPos), RemainingTimeToStartBlinking(3), MinSqrDistanceToSnakeHead(32)
{
	lifeTimeInSeconds = lifeTimeInSecs;
	showFoodOnGridMap = true;

	Game::setTextColors(BackgroundColor, ForegroundColor);
	writeFoodCharacter();

	Timer::setTimerAndCallback(1000, this, &decreaseLifeTime_callBack);
}

void Food::startFoodSpawner()
{
	startMovePosition = GridMap::getStartMovePosition();
	endMovePosition = GridMap::getEndMovePosition();
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

			Game::setTextColors(BackgroundColor, ForegroundColor);
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
		Game::setTextColors(BackgroundColor, ForegroundColor);
	else
		Game::setTextColors(BackgroundColor, BackgroundColor);

	writeFoodCharacter();
}

void Food::runFoodSpawner(void* nullObj)
{
	Point newFoodPosition;
	unsigned char tries = TriesAmount;
	
	do
	{
		if (tries-- == 0)
		{
			Timer::setTimerAndCallback(((rand() % 3) + 2) * 1000, // 0 to 2 plus 2 => (2..4) * 1000
				NULL, &runFoodSpawner);
			return;
		}

		newFoodPosition = GridMap::getRandomPosition();
	
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
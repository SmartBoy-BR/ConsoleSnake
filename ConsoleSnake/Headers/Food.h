/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-23
 *
 * FUNCTION: Snake food definition header.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"

class Snake;

class Food
{
	private:
		const Point					GridPosition;
		const unsigned char			RemainingTimeToStartBlinking;
		const unsigned char			MinSqrDistanceToSnakeHead;
		unsigned char				lifeTimeInSeconds;
		bool						showFoodOnGridMap;
		static std::vector<Food*>	foodsOnGridMap;
		static Point				startMovePosition;
		static Point				endMovePosition;

		static void runFoodSpawner(void*);
		static void decreaseLifeTime_callBack(void* ownerObject);
		static void blinkFoodOnGridMap_callBack(void* ownerObject);

		void writeFoodCharacter();
		void decreaseLifeTime();
		void blinkFoodOnGridMap();

	public:
		static const char	FoodCharacter;
		static const short	PointsPerFood;

		Food(Point& spawnPos, unsigned char lifeTimeInSecs);

		static void startFoodSpawner(Point& startPos, Point& endPos);
		static void stopFoodSpawner();
		static void deleteFoodOnGridMap(Point gridPosition);

};
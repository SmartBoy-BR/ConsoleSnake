/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-23
 *
 * FUNCTION: Snake food definition header.
 */

#pragma once

#include <vector>
#include "../Headers/Point.h"

class Food
{
	private:
		const Point					GridPosition;
		const unsigned char			RemainingTimeToStartBlinking;
		unsigned char				lifeTimeInSeconds;
		bool						showFoodOnGridMap;
		static std::vector<Food*>	foodsOnGridMap;

		static void decreaseLifeTime_callBack(void* ownerObject);
		static void blinkFoodOnGridMap_callBack(void* ownerObject);

		void writeFoodCharacter();
		void decreaseLifeTime();
		void blinkFoodOnGridMap();

	public:
		Food(Point& spawnPos, unsigned char lifeTimeInSecs);
		static const char	FoodCharacter;
		static const short	PointsPerFood;

		static void startFoodSpawner();
		static void deleteFoodOnGridMap(Point gridPosition);

};
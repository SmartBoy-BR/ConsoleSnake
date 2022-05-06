/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-16
 *
 * FUNCTION: Timer source file with the implementations that establish the control of the game's time bases.
 * NOTE: This class can be changed to work independently on a thread.
 */

#include <iostream>
#include <tuple>
#include "../Headers/Timer.h"

bool Timer::isRunning = false;
std::chrono::high_resolution_clock::time_point Timer::previousTimePoint;
std::vector<callbackAndTimersTuple> Timer::methodsAndTimersToAdd;
std::vector<callbackAndTimersTuple> Timer::callbackMethodsAndTimers;

Timer::Timer()
{
}

void Timer::startTimer()
{
	previousTimePoint = std::chrono::high_resolution_clock::now();

	isRunning = true;
}

bool Timer::run()
{
	using namespace std::chrono;

	if (methodsAndTimersToAdd.empty() && callbackMethodsAndTimers.empty())
	{
		isRunning = false;
		return isRunning;
	}

	if (!isRunning)
	{
		startTimer();
	}

	if (isRunning)
	{
		auto msSpam = duration_cast<milliseconds>(high_resolution_clock::now() - previousTimePoint);

		// DECREASES CURRENT TIMERS
		if (msSpam.count() >= 1)
		{
			previousTimePoint = std::chrono::high_resolution_clock::now();

			for (auto& tuple : callbackMethodsAndTimers)
			{
				if (std::get<4>(tuple) == true)
					continue;

				void* ownerObject = std::get<0>(tuple);
				void (*methodPtr)(void*) = std::get<1>(tuple);
				long& currentCounter = std::get<2>(tuple);
				long& originalCounter = std::get<3>(tuple);

				if (--currentCounter <= 0)
				{
					methodPtr(ownerObject);
					currentCounter = originalCounter;
				}
			}
		}

		// DELETES FLAGGED TIMERS
		// NOTE: The "std::remove_if" from "algorithm" library could be used.
		for (size_t idx = callbackMethodsAndTimers.size(); idx > 0; idx--)
		{
			if (std::get<4>(callbackMethodsAndTimers[idx - 1]) == true)
				callbackMethodsAndTimers.erase(callbackMethodsAndTimers.begin() + idx - 1);
		}

		// ADDS TIMERS
		for (auto& tuple : methodsAndTimersToAdd)
		{
			callbackMethodsAndTimers.push_back(tuple);
		}
		methodsAndTimersToAdd.clear();
	}

	return isRunning;
}

void Timer::setTimerAndCallback(long timerInMilliSeconds, void* ownerObject, void (*methodPtr)(void* ownerObject))
{
	// Change the timer if callback already exists.
	for (auto& tuple : callbackMethodsAndTimers)
	{
		if (std::get<0>(tuple) == ownerObject &&
			std::get<1>(tuple) == methodPtr)
		{
			std::get<3>(tuple) = timerInMilliSeconds;
			std::get<4>(tuple) = false;
			return;
		}
	}

	if (methodPtr != NULL)
	{
		methodsAndTimersToAdd.push_back(std::make_tuple(ownerObject, methodPtr, timerInMilliSeconds, timerInMilliSeconds, false));
	}
}

void Timer::markTimerForDeletion(void* ownerObject, void (*methodPtr)(void* ownerObject))
{
	for (auto& tuple : callbackMethodsAndTimers)
	{
		if (std::get<0>(tuple) == ownerObject &&
			std::get<1>(tuple) == methodPtr)
		{
			std::get<4>(tuple) = true;
			return;
		}
	}
}

void Timer::clearAll()
{
	methodsAndTimersToAdd.clear();
	callbackMethodsAndTimers.clear();
}
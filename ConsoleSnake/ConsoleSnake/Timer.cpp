/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-16
 *
 * FUNCTION: Timer source file with the implementations that establish the control of the game's time bases.
 */

#include <iostream>
#include <tuple>
#include "../Headers/Timer.h"

bool Timer::isRunning = false;
std::chrono::high_resolution_clock::time_point Timer::previousTimePoint;
std::vector<std::tuple<long, long>> Timer::timersCounter;
std::vector<void (*)()> Timer::callbackMethods;

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

	if (callbackMethods.size() != timersCounter.size() ||
		callbackMethods.empty()||
		timersCounter.empty())
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

		if (msSpam.count() >= 1)
		{
			for (int i = 0; i < timersCounter.size(); i++) // same as callbackMethods.size()
			{
				long currentCounter = std::get<0>(timersCounter[i]);

				if (--currentCounter > 0)
				{
					std::get<0>(timersCounter[i]) = currentCounter;
				}
				else
				{
					std::get<0>(timersCounter[i]) = std::get<1>(timersCounter[i]);
					callbackMethods[i]();
				}
			}

			previousTimePoint = std::chrono::high_resolution_clock::now();
		}
	}

	return isRunning;
}

void Timer::setTimerAndCallback(long timerInMilliSeconds, void (*fcnPtr)())
{
	if (fcnPtr != NULL)
	{
		// Change the timer if callback already exists.
		for (short indextToDelete = 0; indextToDelete < callbackMethods.size(); indextToDelete++)
		{
			if (callbackMethods[indextToDelete] == fcnPtr)
			{
				std::get<1>(timersCounter[indextToDelete]) = timerInMilliSeconds;
				return;
			}
		}

		callbackMethods.push_back(fcnPtr);
		timersCounter.push_back(std::make_tuple(timerInMilliSeconds, timerInMilliSeconds));
	}
}

void Timer::deleteTimer(void (*fcnPtr)())
{
	short indextToDelete;
	bool hasTimerToDelete = false;

	for (indextToDelete = 0; indextToDelete < callbackMethods.size(); indextToDelete++)
	{
		if (callbackMethods[indextToDelete] == fcnPtr)
		{
			hasTimerToDelete = true;
			break;
		}
	}

	if (hasTimerToDelete)
	{
		callbackMethods.erase(callbackMethods.begin() + indextToDelete);
		timersCounter.erase(timersCounter.begin() + indextToDelete);
	}
}
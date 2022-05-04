/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-16
 *
 * FUNCTION: Timer header with settings to establish time bases needed in parts of the game.
 */

#pragma once

#include <chrono>
#include <vector>

using callbackAndTimersTuple = std::tuple<void*, void (*)(void*), long, long, bool>;

class Timer
{
    private:
        Timer();
        static bool isRunning;
        static std::chrono::high_resolution_clock::time_point previousTimePoint;
        static std::vector<callbackAndTimersTuple> methodsAndTimersToAdd;
        static std::vector<callbackAndTimersTuple> callbackMethodsAndTimers;
        static void startTimer();

    public:
        static bool run();
        static void setTimerAndCallback(long timerInMilliSeconds, void* ownerObject, void (*methodPtr)(void* ownerObject));
        static void markTimerForDeletion(void* ownerObject, void (*methodPtr)(void* ownerObject));
        static void clearAll();
};
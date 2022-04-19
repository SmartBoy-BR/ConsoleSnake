/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-16
 *
 * FUNCTION: Timer header with settings to establish time bases needed in parts of the game.
 */

#pragma once

#include <chrono>
#include <vector>

class Timer
{
    private:
        Timer();
        static bool isRunning;
        static std::chrono::high_resolution_clock::time_point previousTimePoint;
        static std::vector<std::tuple<long, long>> timersCounter;
        static std::vector<void (*)()> callbackMethods;
        static void startTimer();


    public:
        static bool run();
        static void setTimerAndCallback(long timerInMilliSeconds, void (*fcnPtr)());
        static void deleteTimer(void (*fcnPtr)());
};
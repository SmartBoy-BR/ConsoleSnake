// ConsoleSnake.cpp: define o ponto de entrada para o aplicativo.
//
//#define _WIN32_WINNT 0x0500

#include <conio.h>
#include <vector>
#include <Windows.h>
#include "../Headers/Game.h"

using namespace std;

int main()
{
    int ret = 0;
    Game consoleSnake;
    //consoleSnake.testColors();
    ret = consoleSnake.run();

    return ret;
}

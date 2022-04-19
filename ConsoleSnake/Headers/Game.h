/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-10
 *
 * FUNCTION: Game header with settings that are not particular to other elements.
 */

#pragma once

#include <vector>
#include <Windows.h>
#include "../Headers/TitleScreen.h"

enum class ConsoleColor { Black, Blue, Green, Aqua, Red, Purple, Yellow, White, Gray, LightBlue, LightGreen, LightAqua, LightRed, LightPurple, LightYellow, BrightWhite };

enum class GameStates { TitleScreen, WaitOption, GamePlay, Quit };

enum class KeyValues {
    SpecialKey1 = 0x00,
    SpecialKey2 = 0xE0,
    Enter       = 0x0D,
    Up          = 0x48,
    Left        = 0x4B,
    Right       = 0x4D,
    Down        = 0x50
};

class Game
{
    private:
        TitleScreen                 *titleScreen;
        GameStates                  gameStates;
        static HANDLE               handle;
        static COORD                cursorCoord;
        CONSOLE_CURSOR_INFO         *ccInfo;
        HWND                        consoleWindow;
        long                        windowLong;

        void setupConsoleWindow();
        void prepareToCloseWindow();
        bool performTittleScreen();
        void setTextColors(ConsoleColor backgroundColor, ConsoleColor foregroundColor);

    public:
        Game();
        ~Game();
        void run();
        static void setCursorPosition(short x, short y);
        void testColors();
};
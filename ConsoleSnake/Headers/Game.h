#pragma once

#include <vector>
#include <Windows.h>

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
        GameStates gameStates;
        static std::vector<short> TitleScreenBackColors;
        static short numberLimit;
        static short lastRandom;
        static bool enableEnterMessage;
        static HANDLE handle;
        static COORD cursorCoord;
        CONSOLE_CURSOR_INFO* ccInfo;
        HWND consoleWindow;
        long windowLong;
        void setupConsoleWindow();
        void prepareToCloseWindow();
        void drawTitleScreen();
        static void blinkPressEnterMsg();
        static void changeTitleScreenColors();
        bool performTittleScreen();
        void setTextColors(ConsoleColor backgroundColor, ConsoleColor foregroundColor);
        static void setCursorPosition(short x, short y);

    public:
        Game();
        void run();
        void testColors();
};
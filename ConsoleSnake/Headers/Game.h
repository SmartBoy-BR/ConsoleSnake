/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-10
 *
 * FUNCTION: Game header with settings that are not particular to other elements.
 */

#pragma once

#include <vector>
#include <Windows.h>
#include "../Headers/TitleScreen.h"
#include "../Headers/Stage.h"
#include "../Headers/Point.h"

enum class ConsoleColor { Black, Blue, Green, Aqua, Red, Purple, Yellow, White, Gray, LightBlue, LightGreen, LightAqua, LightRed, LightPurple, LightYellow, BrightWhite };

enum class GameStates { TitleScreen, WaitOption, GamePlay, Quit };

enum class KeyValues {
    SpecialKey1 = 0x00,
    SpecialKey2 = 0xE0,
    Enter       = 0x0D,
    ArrowUp     = 0x48, // After a special key.
    ArrowLeft   = 0x4B, // After a special key.
    ArrowRight  = 0x4D, // After a special key.
    ArrowDown   = 0x50  // After a special key.
};

#define CONSOLEWIDTH    114
#define CONSOLEHEIGHT   33

#define GAMEERROR   -1
#define SUCCESS     0
#define BACKTOSTART 1

class Game
{
    private:
        TitleScreen             ptrTitleScreen;
        Stage*                  ptrStage;
        GameStates              gameStates;
        static HANDLE           handle;
        static COORD            cursorCoord;
        CONSOLE_CURSOR_INFO     *ccInfo;
        HWND                    consoleWindow;
        long                    windowLong;

        void setupConsoleWindow();
        void prepareToCloseWindow();

    public:
        static unsigned short	lastHiScorePoints;
        static const Point      StartScreenPoint;
        static const Point      EndScreenPoint;

        Game();
        ~Game();
        int run();
        static void setCursorPosition(SHORT x, SHORT y);
        static void setCursorPosition(const Point& cursorCoordinate);
        static char getCursorPositionData(const Point& cursorCoordinate);
        static void setTextColors(short hexaColorsCode);
        static void setTextColors(ConsoleColor backgroundColor, ConsoleColor foregroundColor);
        void testColors();
};
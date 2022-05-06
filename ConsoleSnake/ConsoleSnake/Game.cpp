/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-10
 *
 * FUNCTION: Source file with the game's global implementations and definitions.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "../Headers/Game.h"
#include "../Headers/Timer.h"

using std::cout;
using std::endl;
using std::string;

HANDLE Game::handle;
COORD Game::cursorCoord;
short Game::lastTitleScreenHexaColors;
unsigned short Game::lastHiScorePoints;
const Point Game::StartScreenPoint = { 3, 1 };
const Point Game::EndScreenPoint = {
    CONSOLEWIDTH - 3, // Minus 1 console border and 2 final white spaces
    CONSOLEHEIGHT - 1 // Minus 1 console border
};

Game::Game()
{
    ptrStage = NULL;
    gameStates = GameStates::TitleScreen;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorCoord = { 0, 0 };
    lastHiScorePoints = 2468;
    ccInfo = new CONSOLE_CURSOR_INFO();
    consoleWindow = NULL;
    windowLong = 0;
    srand((unsigned)time(0));
}

Game::~Game()
{
    delete ptrStage;
    ptrStage = NULL;
}

int Game::run()
{
    setupConsoleWindow();
    bool runningGame = true;

    while (runningGame)
    {
        switch (gameStates)
        {
            case GameStates::TitleScreen:
                gameStates = (ptrTitleScreen.prepareTitleScreen() == SUCCESS)
                    ? GameStates::WaitOption
                    : GameStates::Quit;
                break;

            case GameStates::WaitOption:
                gameStates = GameStates::Quit;

                if (ptrTitleScreen.waitingForPlayerChoice())
                {
                    lastTitleScreenHexaColors = ptrTitleScreen.getHexaColorsCode();

                    ptrStage = new Stage();

                    if (ptrStage == NULL)
                    {
                        cout << "Não foi possível criar \"ptrStage\"." << endl;
                        return GAMEERROR;
                    }

                    gameStates = GameStates::GamePlay;
                }
                break;

            case GameStates::GamePlay:
                switch (ptrStage->run())
                {
                    case GAMEERROR:
                        return GAMEERROR;

                    default:
                    case BACKTOSTART:
                        delete ptrStage;
                        ptrStage = NULL;
                        gameStates = GameStates::TitleScreen;
                        break;
                }
                break;

            case GameStates::Quit:
                runningGame = false;
                break;

            default:
                runningGame = false;
                break;
        }
    }

    prepareToCloseWindow();
    return SUCCESS;
}

void Game::setCursorPosition(SHORT x, SHORT y)
{
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(handle, cursorCoord);
}

void Game::setCursorPosition(const Point& cursorCoordinate)
{
    setCursorPosition(cursorCoordinate.X(), cursorCoordinate.Y());
}

char Game::getCursorPositionData(const Point& cursorCoordinate)
{
    char buffer = ' ';
    DWORD total = 0;
    COORD localCoord;

    localCoord.X = cursorCoordinate.X();
    localCoord.Y = cursorCoordinate.Y();

    ReadConsoleOutputCharacterA(handle, &buffer, 1, localCoord, & total);

    return (total > 0) ? buffer : ' ';
}

void Game::setTextColors(ConsoleColor backgroundColor, ConsoleColor foregroundColor)
{
    short backColor = static_cast<short>(backgroundColor);
    short textColor = static_cast<short>(foregroundColor);

    setConsoleColorsAttribute((backColor << 4) | textColor);
}

void Game::backToTitleScreenColors()
{
    setConsoleColorsAttribute(lastTitleScreenHexaColors);
}

void Game::setupConsoleWindow()
{
    setlocale(LC_ALL, "");
    SetConsoleTitleA("SmartBoy Snake Game");

    system("cls");

    consoleWindow = GetConsoleWindow();
    windowLong = GetWindowLong(consoleWindow, GWL_STYLE);
    SetWindowLong(consoleWindow, GWL_STYLE, windowLong & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    SMALL_RECT smallRect;
    COORD consoleSize;

    consoleSize.X = CONSOLEWIDTH;
    consoleSize.Y = CONSOLEHEIGHT;

    smallRect.Top = smallRect.Left = 0;
    smallRect.Right = consoleSize.X - 1;
    smallRect.Bottom = consoleSize.Y - 1;

    SetConsoleWindowInfo(handle, true, &smallRect);
    SetConsoleScreenBufferSize(handle, consoleSize);

    GetConsoleCursorInfo(handle, ccInfo);
    ccInfo->bVisible = false;
    SetConsoleCursorInfo(handle, ccInfo);
}

void Game::prepareToCloseWindow()
{
    SetWindowLong(consoleWindow, GWL_STYLE, windowLong);
    ccInfo->bVisible = true;
    SetConsoleCursorInfo(handle, ccInfo);

    system("Color 7");
    system("cls");
}

void Game::setConsoleColorsAttribute(short hexaColorsCode)
{
    SetConsoleTextAttribute(handle, hexaColorsCode);
}

void Game::testColors()
{
    if (handle == NULL)
        return;
    
    //std::cout << "┌─┐ └─┘ │ ™ ® © ¤ ▓ ◉    !" << std::endl << std::endl;

    //for (short i = 0; i < 5; i++) //2,3,4,6,8,16,20,30,34,56,57,60,70,80,
    //{
    //    string backColorCmd = "Color ";
    //    backColorCmd.append(std::to_string(i));
    //    system(backColorCmd.c_str());

    //    setCursorPosition(30, 3);
    //    cout << "COR " << i << "\t";
    //    cout << "COR " << i << "\t";
    //    cout << "COR " << i << "\t";
    //    cout << "COR " << i << "\t";
    //    cout << "COR " << i << "\t";
    //    cout << "COR " << i;
    //    Sleep(500);
    //}
    system("Color 7");
    //cout << endl;
    
    short combinedColor = 0x00;

    for (short i = 0; i < 16; i++)
    {
        combinedColor = i;
        combinedColor <<= 4;

        for (short j = 0; j < 16; j++)
        {
            combinedColor &= 0xF0;
            combinedColor |= j;

            //SetConsoleTextAttribute(handle, combinedColor);
            //cout << "Cor " << combinedColor << endl;
            setTextColors(static_cast<ConsoleColor>(i), static_cast<ConsoleColor>(j));
            cout << "Cor " << ((i << 4) | j) << endl;
        }
    }
}
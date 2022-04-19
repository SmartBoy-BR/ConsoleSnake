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

Game::Game()
    :StartScreenPoint(2, 1), EndScreenPoint(CONSOLEWIDTH, CONSOLEHEIGHT - 1)
{
    ptrTitleScreen = new TitleScreen(this);
    gameStates = GameStates::TitleScreen;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorCoord = { 0, 0 };
    ccInfo = new CONSOLE_CURSOR_INFO();
    consoleWindow = NULL;
    windowLong = 0;
    srand((unsigned)time(0));
}

Game::~Game()
{
    delete ptrTitleScreen;
    ptrTitleScreen = NULL;
}

int Game::run()
{
    if (ptrTitleScreen == NULL)
    {
        cout << "Não foi possível criar \"ptrTitleScreen\"." << endl;
        return ERROR;
    }

    setupConsoleWindow();
    bool runningGame = true;

    while (runningGame)
    {
        switch (gameStates)
        {
            case GameStates::TitleScreen:
                gameStates = (ptrTitleScreen->prepareTitleScreen() == SUCCESS)
                    ? GameStates::WaitOption
                    : GameStates::Quit;
                break;

            case GameStates::WaitOption:
                gameStates = GameStates::Quit;

                if (ptrTitleScreen->waitingForPlayerChoice())
                {
                    ptrStage = new Stage(this);

                    if (ptrStage == NULL)
                    {
                        cout << "Não foi possível criar \"ptrStage\"." << endl;
                        return ERROR;
                    }

                    gameStates = GameStates::GamePlay;
                }
                break;

            case GameStates::GamePlay:
                switch (ptrStage->run())
                {
                    case ERROR:
                        return ERROR;

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

void Game::setCursorPosition(short x, short y)
{
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(handle, cursorCoord);
}

void Game::setCursorPosition(Point &cursorCoordinate)
{
    cursorCoord.X = cursorCoordinate.X();
    cursorCoord.Y = cursorCoordinate.Y();
    SetConsoleCursorPosition(handle, cursorCoord);
}

void Game::setTextColors(ConsoleColor backgroundColor, ConsoleColor foregroundColor)
{
    short backColor = static_cast<short>(backgroundColor);
    short textColor = static_cast<short>(foregroundColor);

    SetConsoleTextAttribute(handle, (backColor << 4) | textColor);
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

void Game::testColors()
{
    if (handle == NULL)
        return;
    
    //std::cout << "┌─┐ └─┘ │ ™ ® © ¤ ▓ ◉    !" << std::endl << std::endl;

    for (short i = 0; i < 5; i++) //2,3,4,6,8,16,20,30,34,56,57,60,70,80,
    {
        string backColorCmd = "Color ";
        backColorCmd.append(std::to_string(i));
        system(backColorCmd.c_str());

        setCursorPosition(30, 3);
        cout << "COR " << i << "\t";
        cout << "COR " << i << "\t";
        cout << "COR " << i << "\t";
        cout << "COR " << i << "\t";
        cout << "COR " << i << "\t";
        cout << "COR " << i;
        Sleep(500);
    }
    system("Color 7");
    cout << endl;
    
    //short combinedColor = 0x00;

    //for (short i = 0; i < 16; i++)
    //{
    //    combinedColor = i;
    //    combinedColor <<= 4;

    //    for (short j = 0; j < 16; j++)
    //    {
    //        combinedColor &= 0xF0;
    //        combinedColor |= j;

    //        //SetConsoleTextAttribute(handle, combinedColor);
    //        //cout << "Cor " << combinedColor << endl;
    //        setConsoleColor(static_cast<ConsoleColor>(i), static_cast<ConsoleColor>(j));
    //        cout << "Cor " << ((i << 4) | j) << endl;
    //    }
    //}
}
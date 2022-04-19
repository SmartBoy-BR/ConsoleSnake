/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-10
 *
 * FUNCTION: Source file with the game's global implementations and definitions.
 */

#include <conio.h>
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
{
    titleScreen = new TitleScreen(this);
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
    delete titleScreen;
    titleScreen = NULL;
}

void Game::run()
{
    setupConsoleWindow();
    bool runningGame = true;

    while (runningGame)
    {
        switch (gameStates)
        {
            case GameStates::TitleScreen:
                //drawTitleScreen();
                titleScreen->run();
                //gameStates = GameStates::WaitOption;
                gameStates = GameStates::Quit;
                break;

            case GameStates::WaitOption:
                gameStates = GameStates::Quit;

                if (performTittleScreen())
                {
                    gameStates = GameStates::GamePlay;
                }
                break;

            case GameStates::GamePlay:
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

    consoleSize.X = 113;
    consoleSize.Y = 33;

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

void Game::setTextColors(ConsoleColor backgroundColor, ConsoleColor foregroundColor)
{
    short backColor = static_cast<short>(backgroundColor);
    short textColor = static_cast<short>(foregroundColor);

    SetConsoleTextAttribute(handle, (backColor << 4) | textColor);
}

void Game::setCursorPosition(short x, short y)
{
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(handle, cursorCoord);
}

bool Game::performTittleScreen()
{
    short yPos = 23;
    short key = 0;
    bool startGameplay = false;

    do
    {
        Timer::run();

        if (_kbhit())
        {
            key = _getch();
            setCursorPosition(46, 20);
            cout << std::dec << key << " ";

            if (key == static_cast<short>(KeyValues::SpecialKey1) ||
                key == static_cast<short>(KeyValues::SpecialKey2))
            {
                key = _getch();
                cout << std::dec << key;

                setCursorPosition(52, yPos);
                cout << "  ";

                switch (static_cast<KeyValues>(key))
                {
                    case KeyValues::Up:
                        yPos = 23;
                        startGameplay = true;
                        break;
                    
                    //case KeyValues::Left:
                    //    break;
                    
                    //case KeyValues::Right:
                    //    break;
                    
                    case KeyValues::Down:
                        yPos = 24;
                        startGameplay = false;
                        break;
                    
                    default:
                        break;
                }

                setCursorPosition(52, yPos);
                cout << ">>";
            }
        }

    } while (key != static_cast<short>(KeyValues::Enter));

    return startGameplay;
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
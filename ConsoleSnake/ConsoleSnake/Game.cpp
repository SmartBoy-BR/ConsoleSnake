//#include <chrono>
#include <conio.h> 
//#include <cstdlib> 
//#include <ctime>
#include <iostream>
#include <iomanip>
//#include <sstream>
#include <string>
#include "../Headers/Game.h"
#include "../Headers/Timer.h"

using std::cout;
using std::endl;
using std::string;

std::vector<short> Game::TitleScreenBackColors;
short Game::numberLimit = 0;
short Game::lastRandom = 0;
bool Game::enableEnterMessage;
HANDLE Game::handle;
COORD Game::cursorCoord;

Game::Game()
{
    gameStates = GameStates::TitleScreen;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorCoord = { 0, 0 };
    ccInfo = new CONSOLE_CURSOR_INFO();
    consoleWindow = NULL;
    windowLong = 0;
    srand((unsigned)time(0));
    TitleScreenBackColors = { 1,2,3,4,6,7,8,9,10,11,12,13,14,15,30,32,48,78,87,96,113,125,128,142,159,160,222,224,240 };
    numberLimit = static_cast<short>(TitleScreenBackColors.size());
    enableEnterMessage = false;
    lastRandom = 5; // Default color = 7.
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
                drawTitleScreen();
                gameStates = GameStates::WaitOption;
                break;

            case GameStates::WaitOption:
                gameStates = GameStates::Quit;

                if (performTittleScreen())
                {
                    gameStates = GameStates::GamePlay;
                    Timer::deleteTimer(&Game::blinkPressEnterMsg);
                    Timer::deleteTimer(&Game::changeTitleScreenColors);
                }
                break;

            case GameStates::GamePlay:
                break;

            case GameStates::Quit:
                Timer::deleteTimer(&Game::blinkPressEnterMsg);
                Timer::deleteTimer(&Game::changeTitleScreenColors);
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

void Game::drawTitleScreen()
{
    const short StartXpos = 2;
    const short StartYpos = 1;
    const short LastXpos = 114;

    const string SnakeText[] = {
        " SSSSSS  NN   NN    AAA    KK   KK  EEEEEEE ",
        "SS       NN   NN   AA AA   KK  KK   EE      ",
        "SS       NNN  NN  AA   AA  KK KK    EE      ",
        " SSSSS   NN N NN  AAAAAAA  KKK      EEEEEE  ",
        "     SS  NN  NNN  AA   AA  KK KK    EE      ",
        "     SS  NN   NN  AA   AA  KK  KK   EE      ",
        "SSSSSS   NN   NN  AA   AA  KK   KK  EEEEEEE®"};

    system("cls");
    
    setCursorPosition(StartXpos, StartYpos);
    cout << '+' << std::right << std::setfill('-') << std::setw(LastXpos - StartXpos - 2) << '+' << endl;

    short yPos;
    for (yPos = StartYpos + 1; yPos <= 30 + StartYpos; yPos++)
    {
        setCursorPosition(StartXpos, yPos);
        cout << '|';
        setCursorPosition(LastXpos - 2, yPos);
        cout << '|' << endl;;
    }

    short snakeTxtYpos = 8 + StartYpos;
    short snakeTxtXpos = static_cast<short>((LastXpos + StartXpos - SnakeText[0].length()) * 0.5f);
    short snakeTxtLineLength = sizeof(SnakeText) / sizeof(SnakeText[0]);

    setCursorPosition(snakeTxtXpos, snakeTxtYpos - 1);
    cout << "Console";

    for (short i = 0; i < snakeTxtLineLength; i++)
    {
        setCursorPosition(snakeTxtXpos, snakeTxtYpos + i);
        cout << SnakeText[i];
    }

    cout << std::setfill(' ');
    setCursorPosition(snakeTxtXpos + 17, yPos - 9);
    cout << std::right << std::setw(5) << "Ini" << std::left << std::setw(5) << "cia";
    setCursorPosition(snakeTxtXpos + 17, yPos - 8);
    cout << std::right << std::setw(5) << "Sa" << std::left << std::setw(5) << "ir";
    setCursorPosition(52, yPos - 9);
    cout << ">>";

    string companyString = "© SMARTBOYBR CO..LTD.  2022";
    setCursorPosition(static_cast<short>((LastXpos + StartXpos - companyString.length()) * 0.5f), yPos - 1);
    cout << companyString;

    setCursorPosition(StartXpos, yPos);
    cout << '+' << std::right << std::setfill('-') << std::setw(LastXpos - StartXpos - 2) << '+';

    Timer::setTimerAndCallback(125, &Game::blinkPressEnterMsg);
    Timer::setTimerAndCallback(2000, &Game::changeTitleScreenColors);
}

void Game::blinkPressEnterMsg()
{
    enableEnterMessage = !enableEnterMessage;
    setCursorPosition(52, 21);

    if (enableEnterMessage)
        cout << "Tecle Enter";
    else
        cout << "           ";
}

void Game::changeTitleScreenColors()
{
    short randomNumber;

    do
    {
        randomNumber = (rand() % numberLimit);
    } while (lastRandom == randomNumber);

    lastRandom = randomNumber;

    char colorCmd[10];
    sprintf_s(colorCmd, "Color %x", TitleScreenBackColors[randomNumber]);

    system(colorCmd);
    system(colorCmd);
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
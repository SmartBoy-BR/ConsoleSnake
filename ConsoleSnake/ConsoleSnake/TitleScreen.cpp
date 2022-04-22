/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-18
 *
 * FUNCTION: Source file with the implementations to draw and wait for the user's choice on the start screen.
 */

#include <conio.h>
#include <iostream>
#include <iomanip>
#include "../Headers/TitleScreen.h"
#include "../Headers/Timer.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
using std::string;

bool TitleScreen::enableEnterMessage;
bool TitleScreen::enableChoiceArrow;
Point TitleScreen::blinkMsgPosition;
Point TitleScreen::playerChoiceArrow;
std::vector<short> TitleScreen::TitleScreenBackColors;
short TitleScreen::numberLimit = 0;
short TitleScreen::lastRandom = 0;

TitleScreen::TitleScreen()
{
    enableEnterMessage = false;
    enableChoiceArrow = false;
    blinkMsgPosition = { 52, 21 };
    playerChoiceArrow = { 52, 23 };
    TitleScreenBackColors = { 1,2,3,4,6,7,8,9,10,11,12,13,14,15,30,32,48,78,87,96,113,125,128,142,159,160,222,224,240 };
    numberLimit = static_cast<short>(TitleScreenBackColors.size());
    lastRandom = 5; // Default color = 7.
}

TitleScreen::~TitleScreen()
{
}

int TitleScreen::prepareTitleScreen()
{
    drawTitleScreen();
    Timer::setTimerAndCallback(125, &TitleScreen::blinkPressEnterMsg);
    Timer::setTimerAndCallback(125, &TitleScreen::blinkChoiceArrow);
    Timer::setTimerAndCallback(2000, &TitleScreen::changeTitleScreenColors);

    return SUCCESS;
}

bool TitleScreen::waitingForPlayerChoice()
{
    short yPosUp = playerChoiceArrow.Y();
    short yPosDown = yPosUp + 1;
    short key = 0;
    bool startGameplay = true;

    do
    {
        Timer::run();

        if (_kbhit())
        {
            key = _getch();
            /*Game::setCursorPosition(46, 20);
            Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Black);
            cout << std::dec << key << " ";*/

            if (key == static_cast<short>(KeyValues::SpecialKey1) ||
                key == static_cast<short>(KeyValues::SpecialKey2))
            {
                key = _getch(); // One more reading is needed to get the actual key pressed.
            }

            //cout << std::dec << key;

            switch (key)
            {
                case 'w':
                case 'W':
                case static_cast<short>(KeyValues::ArrowUp):
                    if (!startGameplay)
                    {
                        playerChoiceArrow = { playerChoiceArrow.X(), yPosUp };
                        Game::setCursorPosition(playerChoiceArrow);
                        cout << ">>";
                        Game::setCursorPosition(playerChoiceArrow.X(), yPosDown);
                        cout << "  ";
                        startGameplay = true;
                    }
                    break;

                //case 'a':
                //case 'A':
                //case static_cast<short>(KeyValues::ArrowLeft):
                //    break;

                //case 'd':
                //case 'D':
                //case static_cast<short>(KeyValues::ArrowRight):
                //    break;

                case 's':
                case 'S':
                case static_cast<short>(KeyValues::ArrowDown):
                    if (startGameplay)
                    {
                        playerChoiceArrow = { playerChoiceArrow.X(), yPosDown };
                        Game::setCursorPosition(playerChoiceArrow);
                        cout << ">>";
                        Game::setCursorPosition(playerChoiceArrow.X(), yPosUp);
                        cout << "  ";
                        startGameplay = false;
                    }
                    break;

                default:
                    break;
            }

            /*Game::setCursorPosition(46, 20);
            Game::setTextColors(ConsoleColor::Gray, ConsoleColor::Black);
            cout << playerChoiceArrow.X() << "-" << playerChoiceArrow.Y();*/
        }

    } while (key != static_cast<short>(KeyValues::Enter));

    Timer::deleteTimer(&TitleScreen::blinkPressEnterMsg);
    Timer::deleteTimer(&TitleScreen::blinkChoiceArrow);
    Timer::deleteTimer(&TitleScreen::changeTitleScreenColors);

    return startGameplay;
}

void TitleScreen::drawTitleScreen()
{
    system("cls");

    Point currentDrawPoint(Game::StartScreenPoint); //3,1
    Point endDrawPoint(Game::EndScreenPoint); //111,32

    // DRAW THE BORDERS
    Game::setCursorPosition(currentDrawPoint); // 3,1
    short setW = endDrawPoint.X() - currentDrawPoint.X();
    cout << '+' << std::setfill('-') << std::setw(setW) << '+';

    for (short yPos = currentDrawPoint.Y() + 1; yPos < endDrawPoint.Y(); yPos++)
    {
        Game::setCursorPosition(currentDrawPoint.X(), yPos);
        cout << '|';
        Game::setCursorPosition(endDrawPoint.X(), yPos);
        cout << '|';
    }

    Game::setCursorPosition(currentDrawPoint.X(), endDrawPoint.Y()); //3,32
    cout << '+' << std::setfill('-') << std::setw(setW) << '+';
    
    // DRAW GAME TITLE
    const short consoleStringYpos = 8;
    const string SnakeText[] = {
        " SSSSSS  NN   NN    AAA    KK   KK  EEEEEEE ",
        "SS       NN   NN   AA AA   KK  KK   EE      ",
        "SS       NNN  NN  AA   AA  KK KK    EE      ",
        " SSSSS   NN N NN  AAAAAAA  KKK      EEEEEE  ",
        "     SS  NN  NNN  AA   AA  KK KK    EE      ",
        "     SS  NN   NN  AA   AA  KK  KK   EE      ",
        "SSSSSS   NN   NN  AA   AA  KK   KK  EEEEEEE®" };

    short snakeTxtLineLength = sizeof(SnakeText) / sizeof(SnakeText[0]);
    endDrawPoint += {currentDrawPoint.X() + 2, 0}; // Add start "x" and 2 final white spaces for next calculations.
    currentDrawPoint = { static_cast<short>((endDrawPoint.X() - SnakeText[0].length()) * 0.5f), consoleStringYpos };

    Game::setCursorPosition(currentDrawPoint); //36,8
    cout << "Console";

    for (short i = 0; i < snakeTxtLineLength; i++)
    {
        currentDrawPoint += {0, 1};
        Game::setCursorPosition(currentDrawPoint);
        cout << SnakeText[i];
    }
    
    // DRAW PLAYER OPTIONS
    currentDrawPoint += {19, 8};
    Game::setCursorPosition(currentDrawPoint);//55,23
    cout << "Inicia";
    currentDrawPoint += {1, 1};
    Game::setCursorPosition(currentDrawPoint);//56,24
    cout << "Sair";

    // DRAW CMOPANY INFO
    string companyString = "© SMARTBOYBR CO., LTD. 2022 ALL RIGHTS RESERVED.";
    currentDrawPoint = { static_cast<short>((endDrawPoint.X() - companyString.length()) * 0.5f), endDrawPoint.Y() - 1};
    Game::setCursorPosition(currentDrawPoint);//(116-48)*0.5,32-1 => 34,31
    cout << companyString;
}

void TitleScreen::blinkPressEnterMsg()
{
    enableEnterMessage = !enableEnterMessage;
    Game::setCursorPosition(blinkMsgPosition);

    if (enableEnterMessage)
        cout << "Tecle Enter!";
    else
        cout << "            ";
}

void TitleScreen::blinkChoiceArrow()
{
    enableChoiceArrow = !enableChoiceArrow;
    Game::setCursorPosition(playerChoiceArrow);

    if (enableChoiceArrow)
        cout << ">>";
    else
        cout << "  ";
}

void TitleScreen::changeTitleScreenColors()
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
    system(colorCmd); // Sometimes some borders remains in old color (bug?), then force color change.
}
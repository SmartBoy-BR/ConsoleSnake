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
std::vector<short> TitleScreen::TitleScreenBackColors;
short TitleScreen::numberLimit = 0;
short TitleScreen::lastRandom = 0;

TitleScreen::TitleScreen(Game *refGame)
    : game(refGame)
{
    enableEnterMessage = false;
    TitleScreenBackColors = { 1,2,3,4,6,7,8,9,10,11,12,13,14,15,30,32,48,78,87,96,113,125,128,142,159,160,222,224,240 };
    numberLimit = static_cast<short>(TitleScreenBackColors.size());
    lastRandom = 5; // Default color = 7.
}

void TitleScreen::run()
{
    drawTitleScreen();
    while (!_kbhit()) Timer::run();
    Timer::deleteTimer(&TitleScreen::blinkPressEnterMsg);
    Timer::deleteTimer(&TitleScreen::changeTitleScreenColors);
}

void TitleScreen::drawTitleScreen()
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
        "SSSSSS   NN   NN  AA   AA  KK   KK  EEEEEEE®" };

    system("cls");

    Game::setCursorPosition(StartXpos, StartYpos);
    cout << '+' << std::right << std::setfill('-') << std::setw(LastXpos - StartXpos - 2) << '+' << endl;

    short yPos;
    for (yPos = StartYpos + 1; yPos <= 30 + StartYpos; yPos++)
    {
        Game::setCursorPosition(StartXpos, yPos);
        cout << '|';
        Game::setCursorPosition(LastXpos - 2, yPos);
        cout << '|' << endl;;
    }

    short snakeTxtYpos = 8 + StartYpos;
    short snakeTxtXpos = static_cast<short>((LastXpos + StartXpos - SnakeText[0].length()) * 0.5f);
    short snakeTxtLineLength = sizeof(SnakeText) / sizeof(SnakeText[0]);

    Game::setCursorPosition(snakeTxtXpos, snakeTxtYpos - 1);
    cout << "Console";

    for (short i = 0; i < snakeTxtLineLength; i++)
    {
        Game::setCursorPosition(snakeTxtXpos, snakeTxtYpos + i);
        cout << SnakeText[i];
    }

    cout << std::setfill(' ');
    Game::setCursorPosition(snakeTxtXpos + 17, yPos - 9);
    cout << std::right << std::setw(5) << "Ini" << std::left << std::setw(5) << "cia";
    Game::setCursorPosition(snakeTxtXpos + 17, yPos - 8);
    cout << std::right << std::setw(5) << "Sa" << std::left << std::setw(5) << "ir";
    Game::setCursorPosition(52, yPos - 9);
    cout << ">>";

    string companyString = "© SMARTBOYBR CO..LTD.  2022";
    Game::setCursorPosition(static_cast<short>((LastXpos + StartXpos - companyString.length()) * 0.5f), yPos - 1);
    cout << companyString;

    Game::setCursorPosition(StartXpos, yPos);
    cout << '+' << std::right << std::setfill('-') << std::setw(LastXpos - StartXpos - 2) << '+';

    Timer::setTimerAndCallback(125, &TitleScreen::blinkPressEnterMsg);
    Timer::setTimerAndCallback(2000, &TitleScreen::changeTitleScreenColors);
}

void TitleScreen::blinkPressEnterMsg()
{
    enableEnterMessage = !enableEnterMessage;
    Game::setCursorPosition(52, 21);

    if (enableEnterMessage)
        cout << "Tecle Enter";
    else
        cout << "           ";
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
    system(colorCmd);
}
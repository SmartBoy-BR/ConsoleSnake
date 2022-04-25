/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-20
 *
 * FUNCTION: Source file with the implementations for drawing and managing the user interface.
 */

#include <iostream>
#include <iomanip>
#include "../Headers/UI.h"
#include "../Headers/Timer.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
using std::string;

bool UI::showScorePoints;
bool UI::showHiScorePoints;
bool UI::showSpeedValue;
Point UI::scorePanelPosition;
Point UI::hiScorePanelPosition;
Point UI::snakeSpeedPanelPosition;
unsigned short UI::scorePanelPoints;
unsigned short UI::pointsToAdd;
unsigned short UI::hiScorePanelPoints;
unsigned short UI::snakeSpeedPanelValue;
unsigned short UI::speedToDecrement;
std::vector<void (*)()> UI::blinkMethods;

UI::UI()
{
	showScorePoints = false;
	showHiScorePoints = false;
	showSpeedValue = false;

	// Positions are changed inside "drawUI"
	scorePanelPosition = { 9, 3 }; 
	hiScorePanelPosition = { 32, 3 };
	snakeSpeedPanelPosition = { 56, 3 };

	scorePanelPoints = 0;
	pointsToAdd = 0;
	hiScorePanelPoints = Game::lastHiScorePoints;
	snakeSpeedPanelValue = 250;
	speedToDecrement = 0;
}

void UI::setupUI()
{
	drawUI();
}

void UI::addScorePoints(unsigned short morePoints)
{
	deleteUItimers();

	pointsToAdd += morePoints;

	blinkMethods.push_back(&UI::blinkScore);

	if (hiScorePanelPoints < scorePanelPoints + pointsToAdd)
		blinkMethods.push_back(&UI::blinkHiScore);

	if (((scorePanelPoints + pointsToAdd) % 300) == 0)
	{
		speedToDecrement = 25;
		blinkMethods.push_back(&UI::blinkSpeedValue);
	}

	Timer::setTimerAndCallback(1000, &UI::prepareToStopBlinking);

	for (auto method : blinkMethods)
		Timer::setTimerAndCallback(100, method);
}

unsigned short UI::getSpeedPanelValue()
{
	return snakeSpeedPanelValue;
}

void UI::deleteUItimers()
{
	Timer::deleteTimer(&UI::prepareToStopBlinking);
	Timer::deleteTimer(&UI::stopBlinking);

	for (auto method : blinkMethods)
		Timer::deleteTimer(method);

	Timer::deleteTimer(&UI::stopBlinking);
	blinkMethods.clear();

	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightGreen);
	writeScore();
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightAqua);
	writeHiScore();
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Yellow);
	writeSpeedValue();
}

void UI::drawUI()
{
	//const short 
	Point currentDrawPoint(Game::StartScreenPoint); //3,1
	Point endDrawPoint(Game::EndScreenPoint); //111,32

	// ADJUSTS FOR INTERFACE LIMITS
	currentDrawPoint += {6, 2}; //9,3
	endDrawPoint -= {6, 27}; //105,5

	// SETS UI MAIN COLOR
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::BrightWhite);

	// DRAW THE PANEL BORDERS
	Game::setCursorPosition(hiScorePanelPosition.X(), hiScorePanelPosition.Y() + 1); //32,4
	cout << '|';
	Game::setCursorPosition(snakeSpeedPanelPosition.X(), snakeSpeedPanelPosition.Y() + 1); //56,4
	cout << '|';
	Game::setCursorPosition(endDrawPoint.X(), endDrawPoint.Y() - 1); //105,4
	cout << '|';

	short setWscoreToHiScore = hiScorePanelPosition.X() - scorePanelPosition.X(); //23
	short setWhiScoreToSnakePanel = snakeSpeedPanelPosition.X() - hiScorePanelPosition.X(); //24
	short setWsnakePanelToEndPanels = endDrawPoint.X() - snakeSpeedPanelPosition.X(); //(105-56) 49

	Game::setCursorPosition(currentDrawPoint); //9,3
	cout << '+' << std::setfill('-') << std::setw(setWscoreToHiScore) << '+'
		<< std::setw(setWhiScoreToSnakePanel) << '+'
		<< std::setw(setWsnakePanelToEndPanels) << '+';

	Game::setCursorPosition(currentDrawPoint.X(), endDrawPoint.Y()); //9,5
	cout << '+' << std::setfill('-') << std::setw(setWscoreToHiScore) << '+'
		<< std::setw(setWhiScoreToSnakePanel) << '+'
		<< std::setw(setWsnakePanelToEndPanels) << '+';

	// DRAW PANEL INFO
	scorePanelPosition += { 0, 1 };
	hiScorePanelPosition += { 0, 1 };
	snakeSpeedPanelPosition += { 0, 1 };
	Game::setCursorPosition(scorePanelPosition); //11,4
	cout << "| PLACAR: ";
	Game::setCursorPosition(hiScorePanelPosition); //34,4
	cout << "| RECORDE: ";
	Game::setCursorPosition(snakeSpeedPanelPosition); //58,4
	cout << "| TEMPO DE MOVIMENTAÇÃO: ";

	scorePanelPosition += { 10, 0 };
	hiScorePanelPosition += { 11, 0 };
	snakeSpeedPanelPosition += { 25, 0 };
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightGreen);
	writeScore();
	cout << " pts  ";
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightAqua);
	writeHiScore();
	cout << " pts  ";
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Yellow);
	writeSpeedValue();
	cout << " milissegundos       ";
}

void UI::blinkScore()
{
	showScorePoints = !showScorePoints;

	if (showScorePoints)
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightGreen);
	else
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Purple);

	writeScore();
}

void UI::blinkHiScore()
{
	showHiScorePoints = !showHiScorePoints;

	if (showHiScorePoints)
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightAqua);
	else
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Purple);

	writeHiScore();
}

void UI::blinkSpeedValue()
{
	showSpeedValue = !showSpeedValue;

	if (showSpeedValue)
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Yellow);
	else
		Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Purple);

	writeSpeedValue();
}

void UI::writeScore()
{
	Game::setCursorPosition(scorePanelPosition); //19,4
	cout << std::setfill('0') << std::setw(7) << scorePanelPoints;
}

void UI::writeHiScore()
{
	Game::setCursorPosition(hiScorePanelPosition); //43,4
	cout << std::setfill('0') << std::setw(7) << hiScorePanelPoints;
}

void UI::writeSpeedValue()
{
	Game::setCursorPosition(snakeSpeedPanelPosition); //86,4
	cout << std::setfill('0') << std::setw(3) << snakeSpeedPanelValue;
}

void UI::prepareToStopBlinking()
{
	scorePanelPoints += pointsToAdd;
	pointsToAdd = 0;

	if (hiScorePanelPoints < scorePanelPoints)
		hiScorePanelPoints = scorePanelPoints;

	snakeSpeedPanelValue -= speedToDecrement;
	speedToDecrement = 0;
	
	Timer::setTimerAndCallback(1000, &UI::stopBlinking);
	
	for (auto method : blinkMethods)
		Timer::setTimerAndCallback(200, method);
	
	Timer::deleteTimer(&UI::prepareToStopBlinking);
}

void UI::stopBlinking()
{
	for (auto method : blinkMethods)
		Timer::deleteTimer(method);
	
	Timer::deleteTimer(&UI::stopBlinking);

	showScorePoints = false;
	showHiScorePoints = false;
	showSpeedValue = false;
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightGreen);
	writeScore();
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightAqua);
	writeHiScore();
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Yellow);
	writeSpeedValue();

	blinkMethods.clear();
}
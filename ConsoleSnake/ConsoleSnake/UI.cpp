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

Point UI::scorePanelPosition;
Point UI::hiScorePanelPosition;
Point UI::snakeSpeedPanelPosition;
unsigned short UI::scorePanelPoints;
unsigned short UI::hiScorePanelPoints;
unsigned short UI::snakeSpeedPanelValue;

UI::UI()
{
	// Positions are changed inside "drawUI"
	scorePanelPosition = { 9, 3 }; 
	hiScorePanelPosition = { 32, 3 };
	snakeSpeedPanelPosition = { 56, 3 };

	scorePanelPoints = 1;
	hiScorePanelPoints = Game::lastHiScorePoints;
	snakeSpeedPanelValue = 1;
}

void UI::setupUI()
{
	drawUI();
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
	//Game::setCursorPosition(hiScorePanelPosition); //32,3
	//cout << '+';
	Game::setCursorPosition(hiScorePanelPosition.X(), hiScorePanelPosition.Y() + 1); //32,4
	cout << '|';
	//Game::setCursorPosition(snakeSpeedPanelPosition); //56,3
	//cout << '+';
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
	//scorePanelPosition += { 2, 1 };
	scorePanelPosition += { 0, 1 };
	//hiScorePanelPosition += { 2, 1 };
	hiScorePanelPosition += { 0, 1 };
	//snakeSpeedPanelPosition += { 2, 1 };
	snakeSpeedPanelPosition += { 0, 1 };
	Game::setCursorPosition(scorePanelPosition); //11,4
	cout << "| PLACAR: ";
	Game::setCursorPosition(hiScorePanelPosition); //34,4
	cout << "| RECORDE: ";
	Game::setCursorPosition(snakeSpeedPanelPosition); //58,4
	cout << "| TEMPO DE MOVIMENTAÇÃO: ";
	//scorePanelPosition += { 8, 0 };
	scorePanelPosition += { 10, 0 };
	//hiScorePanelPosition += { 9, 0 };
	hiScorePanelPosition += { 11, 0 };
	//snakeSpeedPanelPosition += { 23, 0 };
	snakeSpeedPanelPosition += { 25, 0 };
	addScorePoints(0);
	cout << " pts  ";
	updateHiScorePoints();
	cout << " pts  ";
	updateSnakeSpeedValue(1);
	cout << "      ";
}

void UI::addScorePoints(unsigned short morePoints)
{
	scorePanelPoints += morePoints;

	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightGreen);

	Game::setCursorPosition(scorePanelPosition); //19,4
	cout << std::setfill('0') << std::setw(7) << scorePanelPoints;
}

void UI::updateHiScorePoints()
{
	//hiScorePanelPoints = scorePanelPoints;

	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightAqua);

	Game::setCursorPosition(hiScorePanelPosition); //43,4
	cout << std::setfill('0') << std::setw(7) << hiScorePanelPoints;
}

void UI::updateSnakeSpeedValue(unsigned short newSpeed)
{
	snakeSpeedPanelValue = newSpeed;
	const string snakeSpeedPanelText = "900 microssegundos";

	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Yellow);

	Game::setCursorPosition(snakeSpeedPanelPosition); //86,4
	cout << snakeSpeedPanelText;
}
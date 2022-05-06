/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-20
 *
 * FUNCTION: Source file with the implementations for drawing and managing the user interface.
 * NOTE: Each panel can be an object of a class to better separate tasks.
 */

#include <iostream>
#include <iomanip>
#include "../Headers/UI.h"
#include "../Headers/Timer.h"
#include "../Headers/Stage.h"
#include "../Headers/Game.h"

using std::cout;
using std::endl;
using std::string;

UI::UI()
	: PointsToIncreaseSpeed(300), StartTimeSpeed(260), MinimumTimeSpeed(38)
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
	snakeSpeedPanelValue = StartTimeSpeed;
	nextSnakeSpeedValue = snakeSpeedPanelValue;
}

void UI::setupUI()
{
	drawUI();
}

void UI::addScorePoints(unsigned short morePoints)
{
	deleteUItimers();

	pointsToAdd += morePoints;

	blinkMethods.push_back(&UI::blinkScore_callBack);

	if (hiScorePanelPoints < scorePanelPoints + pointsToAdd)
	{
		blinkMethods.push_back(&UI::blinkHiScore_callBack);
		Game::lastHiScorePoints = scorePanelPoints + pointsToAdd;
	}

	if (nextSnakeSpeedValue > MinimumTimeSpeed &&
		((scorePanelPoints + pointsToAdd) % PointsToIncreaseSpeed) == 0)
	{
		setNextSpeedPanelValue();

		if (nextSnakeSpeedValue == MinimumTimeSpeed)
			Timer::setTimerAndCallback(200, this, &UI::blinkSpeedValue_callBack);
		else
			blinkMethods.push_back(&UI::blinkSpeedValue_callBack);
	}

	Timer::setTimerAndCallback(1000, this, &UI::prepareToStopBlinking_callBack);

	for (auto method : blinkMethods)
		Timer::setTimerAndCallback(100, this, method);
}

unsigned short UI::getNextSpeedPanelValue()
{
	return nextSnakeSpeedValue;
}

void UI::deleteUItimers()
{
	Timer::markTimerForDeletion(this, &UI::prepareToStopBlinking_callBack);
	Timer::markTimerForDeletion(this, &UI::stopBlinking_callBack);

	for (auto method : blinkMethods)
		Timer::markTimerForDeletion(this, method);

	blinkMethods.clear();

	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightGreen);
	writeScore();
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::LightAqua);
	writeHiScore();
	Game::setTextColors(ConsoleColor::Purple, ConsoleColor::Yellow);
	writeSpeedValue();
}

void UI::setNextSpeedPanelValue()
{
	if (nextSnakeSpeedValue <= MinimumTimeSpeed)
	{
		nextSnakeSpeedValue = MinimumTimeSpeed;
		return;
	}

	// Some logic to change and limit the speed.
	if (nextSnakeSpeedValue > StartTimeSpeed - 35 - 35) nextSnakeSpeedValue = nextSnakeSpeedValue - 35; //> 190
	else if (nextSnakeSpeedValue > StartTimeSpeed - 70 - 30 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 30; //> 130
	else if (nextSnakeSpeedValue > StartTimeSpeed - 130 - 20 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 20; //> 90
	else if (nextSnakeSpeedValue > StartTimeSpeed - 170 - 10 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 10; //> 70
	else if (nextSnakeSpeedValue > StartTimeSpeed - 190 - 7 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 7; //> 56
	else if (nextSnakeSpeedValue > StartTimeSpeed - 204 - 5 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 5; //> 46
	else if (nextSnakeSpeedValue > StartTimeSpeed - 214 - 3 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 3; //> 40
	else if (nextSnakeSpeedValue > StartTimeSpeed - 220 - 1 * 2) nextSnakeSpeedValue = nextSnakeSpeedValue - 1; //> 38
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
	cout << Stage::BorderCharacter;
	Game::setCursorPosition(snakeSpeedPanelPosition.X(), snakeSpeedPanelPosition.Y() + 1); //56,4
	cout << Stage::BorderCharacter;
	Game::setCursorPosition(endDrawPoint.X(), endDrawPoint.Y() - 1); //105,4
	cout << Stage::BorderCharacter;

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
	cout << Stage::BorderCharacter << " PLACAR: ";
	Game::setCursorPosition(hiScorePanelPosition); //34,4
	cout << Stage::BorderCharacter << " RECORDE: ";
	Game::setCursorPosition(snakeSpeedPanelPosition); //58,4
	cout << Stage::BorderCharacter << " TEMPO DE MOVIMENTAÇÃO: ";

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

	snakeSpeedPanelValue = nextSnakeSpeedValue;
	
	Timer::setTimerAndCallback(1000, this, &UI::stopBlinking_callBack);
	
	for (auto method : blinkMethods)
		Timer::setTimerAndCallback(200, this, method);
	
	Timer::markTimerForDeletion(this, &UI::prepareToStopBlinking_callBack);
}

void UI::stopBlinking()
{
	for (auto method : blinkMethods)
		Timer::markTimerForDeletion(this, method);
	
	Timer::markTimerForDeletion(this, &UI::stopBlinking_callBack);

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

void UI::blinkScore_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->blinkScore();
}

void UI::blinkHiScore_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->blinkHiScore();
}

void UI::blinkSpeedValue_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->blinkSpeedValue();
}

void UI::prepareToStopBlinking_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->prepareToStopBlinking();
}

void UI::stopBlinking_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->stopBlinking();
}
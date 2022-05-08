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

const vector<ushort> UI::SnakeSpeedTimes = { 38, 39, 40, 43, 46, 51, 56, 63, 70, 80, 90, 110, 130, 160, 190, 225, 260 };

UI::UI() :
	BackgroundColor(Stage::ForegroundColor), ScoreForegroundColor(ConsoleColor::LightGreen),
	HiScoreForegroundColor(ConsoleColor::LightAqua), SpeedForegroundColor(ConsoleColor::Yellow),
	PointsToIncreaseSpeed(300)
{
	showScorePoints = true;
	showHiScorePoints = true;
	showSpeedValue = true;

	// Positions are changed inside "drawUI"
	scorePanelPosition = { 9, 3 }; 
	hiScorePanelPosition = { 32, 3 };
	snakeSpeedPanelPosition = { 56, 3 };

	scorePanelPoints = 0;
	nextScoreValue = 0;
	hiScorePanelPoints = Game::lastHiScorePoints;
	speedTimeIndex = static_cast<ushort>(SnakeSpeedTimes.size()) - 1;
	nextSnakeSpeedTime = SnakeSpeedTimes[speedTimeIndex];
	snakeSpeedPanelValue = nextSnakeSpeedTime;
}

void UI::setupUI()
{
	drawUI();
}

void UI::addScorePoints(ushort pointsToAdd)
{
	deleteUItimers();

	nextScoreValue += pointsToAdd;

	blinkMethods.push_back(&UI::blinkScore_callBack);

	if (hiScorePanelPoints < nextScoreValue)
	{
		blinkMethods.push_back(&UI::blinkHiScore_callBack);
		Game::lastHiScorePoints = nextScoreValue;
	}

	if (nextSnakeSpeedTime > SnakeSpeedTimes[0] &&
		(nextScoreValue % PointsToIncreaseSpeed) == 0)
	{
		nextSnakeSpeedTime = SnakeSpeedTimes[--speedTimeIndex];

		if (nextSnakeSpeedTime == SnakeSpeedTimes[0])
			Timer::setTimerAndCallback(200, this, &UI::blinkSpeedValue_callBack);
		else
			blinkMethods.push_back(&UI::blinkSpeedValue_callBack);
	}

	Timer::setTimerAndCallback(1000, this, &UI::prepareToStopBlinking_callBack);

	for (auto method : blinkMethods)
		Timer::setTimerAndCallback(100, this, method);
}

ushort UI::getNextSpeedPanelValue() { return nextSnakeSpeedTime; }
ushort UI::getMinimumTimeSpeed() { return SnakeSpeedTimes[0]; }

void UI::deleteUItimers()
{
	Timer::markTimerForDeletion(this, &UI::prepareToStopBlinking_callBack);
	Timer::markTimerForDeletion(this, &UI::stopBlinking_callBack);

	for (auto method : blinkMethods)
		Timer::markTimerForDeletion(this, method);

	blinkMethods.clear();

	writeAllPanelValues();
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
	Game::setTextColors(BackgroundColor, ConsoleColor::BrightWhite);

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
	Game::setTextColors(BackgroundColor, ScoreForegroundColor);
	writePanelValue(scorePanelPosition, 7, scorePanelPoints);
	cout << " pts  ";
	Game::setTextColors(BackgroundColor, HiScoreForegroundColor);
	writePanelValue(hiScorePanelPosition, 7, hiScorePanelPoints);
	cout << " pts  ";
	Game::setTextColors(BackgroundColor, SpeedForegroundColor);
	writePanelValue(snakeSpeedPanelPosition, 3, snakeSpeedPanelValue);
	cout << " milissegundos       ";
}

void UI::blinkPanelValue(bool& showPanelValue, const ConsoleColor& valueForegroundColor)
{
	showPanelValue = !showPanelValue;
	
	if (showPanelValue)
		Game::setTextColors(BackgroundColor, valueForegroundColor);
	else
		Game::setTextColors(BackgroundColor, BackgroundColor);
}

void UI::writePanelValue(const Point& panelPosition, const uchar setW, const ushort& panelValue)
{
	Game::setCursorPosition(panelPosition);
	cout << std::setfill('0') << std::setw(setW) << panelValue;
}

void UI::writeAllPanelValues()
{
	Game::setTextColors(BackgroundColor, ScoreForegroundColor);
	writePanelValue(scorePanelPosition, 7, scorePanelPoints);
	Game::setTextColors(BackgroundColor, HiScoreForegroundColor);
	writePanelValue(hiScorePanelPosition, 7, hiScorePanelPoints);
	Game::setTextColors(BackgroundColor, SpeedForegroundColor);
	writePanelValue(snakeSpeedPanelPosition, 3, snakeSpeedPanelValue);
}

void UI::prepareToStopBlinking()
{
	scorePanelPoints = nextScoreValue;

	if (hiScorePanelPoints < scorePanelPoints)
		hiScorePanelPoints = scorePanelPoints;

	snakeSpeedPanelValue = nextSnakeSpeedTime;
	
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

	showScorePoints = true;
	showHiScorePoints = true;
	showSpeedValue = true;
	writeAllPanelValues();

	blinkMethods.clear();
}

void UI::blinkScore_callBack(void* ownerObject)
{
	UI* ptrUi = reinterpret_cast<UI*>(ownerObject);
	ptrUi->blinkPanelValue(ptrUi->showScorePoints, ptrUi->ScoreForegroundColor);
	ptrUi->writePanelValue(ptrUi->scorePanelPosition, 7, ptrUi->scorePanelPoints);
}

void UI::blinkHiScore_callBack(void* ownerObject)
{
	UI* ptrUi = reinterpret_cast<UI*>(ownerObject);
	ptrUi->blinkPanelValue(ptrUi->showHiScorePoints, ptrUi->HiScoreForegroundColor);
	ptrUi->writePanelValue(ptrUi->hiScorePanelPosition, 7, ptrUi->hiScorePanelPoints);
}

void UI::blinkSpeedValue_callBack(void* ownerObject)
{
	UI* ptrUi = reinterpret_cast<UI*>(ownerObject);
	ptrUi->blinkPanelValue(ptrUi->showSpeedValue, ptrUi->SpeedForegroundColor);
	ptrUi->writePanelValue(ptrUi->snakeSpeedPanelPosition, 3, ptrUi->snakeSpeedPanelValue);
}

void UI::prepareToStopBlinking_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->prepareToStopBlinking();
}

void UI::stopBlinking_callBack(void* ownerObject)
{
	reinterpret_cast<UI*>(ownerObject)->stopBlinking();
}
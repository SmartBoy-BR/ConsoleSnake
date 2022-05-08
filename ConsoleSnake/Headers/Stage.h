/* CREATED BY:      SmartBoyBR (A. Rodrigo Moreira)
 * CREATED DATE:    2022-Apr-17
 *
 * FUNCTION: Game level header with global gameplay system settings.
 */

#pragma once

#include "../Headers/Point.h"
#include "../Headers/UI.h"
#include "../Headers/GridMap.h"

enum class ConsoleColor;

class Stage
{
	private:
		UI			ui;
		GridMap*	gridMap;

		void drawStageScreen();

	public:
		static const ConsoleColor BackgroundColor;
		static const ConsoleColor ForegroundColor;
		static const char BorderCharacter;

		Stage();
		~Stage();
		int run();
};
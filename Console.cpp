//Console.cpp
#include "Console.h"

#include "Point.h"
#include <Windows.h>

import std;

void Console::clear() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) { return; }

	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	COORD writeCoord = { 0, 0 };
	DWORD written;//该变量值无需使用，仅为 API 要求传入

	FillConsoleOutputCharacterW(hStdout, ' ', length, writeCoord, &written);
	SetConsoleCursorPosition(hStdout, writeCoord);
}

void Console::setCursorVis(bool visible) {
	CONSOLE_CURSOR_INFO cci;
	if (!GetConsoleCursorInfo(hStdout, &cci)) { return; }

	cci.bVisible = visible;
	SetConsoleCursorInfo(hStdout, &cci);
}

void Console::setCursorPos(Point<int> pos) {
	COORD cursorPos = { static_cast<SHORT>(pos.x), static_cast<SHORT>(pos.y) };
	SetConsoleCursorPosition(hStdout, cursorPos);
}

void Console::setTextColor(Color color) {
	SetConsoleTextAttribute(hStdout, std::to_underlying(color));
}

Point<int> Console::getWindowSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) { 
		return Point(0, 0);
	}

	int x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return Point(x, y);
}

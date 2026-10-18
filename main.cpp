//main.cpp
#include "Console.h"
#include "Game.h"

import std;

//全局对象声明
Game game;

int main() {
	Console::setCursorVis(false);

	//运行游戏
	game.run();

	Console::clear();
}

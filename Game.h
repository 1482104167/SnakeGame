//Game.h
#pragma once

#include "GameEngine.h"
#include "Renderer.h"

class Game {
public:
	//运行游戏
	void run();

private:
	//页面导航
	enum class PageNav : unsigned char {
		Enter, Start, Play, Settings, Exit
	};

	//显示进入页面
	PageNav showEnterPage();
	//显示开始页面
	PageNav showStartPage();
	//显示游玩页面
	PageNav showPlayPage();
	//显示设置页面
	PageNav showSettingsPage();

	//游戏主循环
	void mainLoop();

	GameEngine engine_;
	Renderer renderer_;
};

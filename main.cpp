//main.cpp
#include "Console.h"
#include "GameEngine.h"
#include "LobbyPage.h"
#include "PageBase.h"
#include "Renderer.h"
#include "SysTimerRes.h"

import std;

int main() {
	GameEngine engine;
	Renderer renderer;
	GameContext ctx = { engine, renderer };

	Console::setCursorVis(false);

	//提高系统计时器分辨率，使 sleep 延时更精确
	SysTimerRes timerRes(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	std::unique_ptr<PageBase> page = std::make_unique<LobbyPage>();
	while (page) {
		page->onEnter(ctx);
		auto nextPage = page->run(ctx);
		page->onExit(ctx);
		page = std::move(nextPage);
	}

	Console::clear();
}

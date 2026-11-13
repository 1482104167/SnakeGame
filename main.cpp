//main.cpp
#include "Console.h"
#include "EnteringPage.h"
#include "GameEngine.h"
#include "PageBase.h"
#include "Renderer.h"
#include "SysTimerRes.h"

import std;

//全局对象声明
GameEngine engine;
Renderer renderer;
GameContext ctx = { engine, renderer };

int main() {
	Console::setCursorVis(false);

	//提高系统计时器分辨率，使 sleep 延时更精确
	SysTimerRes timerRes(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	std::unique_ptr<PageBase> page = std::make_unique<EnteringPage>();
	while (page) {
		page->onEnter(ctx);
		auto nextPage = page->run(ctx);
		page->onExit(ctx);
		page = std::move(nextPage);
	}

	Console::clear();
}

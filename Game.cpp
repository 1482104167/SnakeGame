//Game.cpp
//#include "Game.h"
//
//#include "PageBase.h"
//#include "Pages.h"
//#include "SysTimerRes.h"
//
//import std;
//
//void Game::run() {
//	//提高系统计时器分辨率，使 sleep 延时更精确
//	SysTimerRes timerRes(1);
//	std::this_thread::sleep_for(std::chrono::milliseconds(300));
//
//	GameContext ctx = { engine_, renderer_ };
//
//	std::unique_ptr<PageBase> page = std::make_unique<EnterPage>();
//	while (page) {
//		page = page->run(ctx);
//	}
//}

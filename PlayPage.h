//PlayPage.h
#pragma once

#include "PageBase.h"
#include <memory>

class PlayPage : public PageBase {
public:
	void onEnter(GameContext& ctx) override;
	void onExit(GameContext& ctx) override;
	std::unique_ptr<PageBase> run(GameContext& ctx) override;

private:
	//游戏主循环
	void mainLoop(GameContext& ctx);
};

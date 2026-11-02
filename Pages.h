//Pages.h
#pragma once

#include "PageBase.h"
#include <memory>

//进入页面
class EnteringPage : public PageBase {
public:
	std::unique_ptr<PageBase> run(GameContext& ctx) override;
};

//开始页面
class StartingPage : public PageBase {
public:
	std::unique_ptr<PageBase> run(GameContext& ctx) override;
};

//游玩页面
class PlayingPage : public PageBase {
public:
	std::unique_ptr<PageBase> run(GameContext& ctx) override;

private:
	//游戏主循环
	void mainLoop(GameContext& ctx);
};

//设置页面
class SettingsPage : public PageBase {
public:
	std::unique_ptr<PageBase> run(GameContext& ctx) override;
};

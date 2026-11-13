//PlayingPage.cpp
#include "PlayingPage.h"

#include "EnteringPage.h"
#include "GameCommand.h"
#include "GameEngine.h"
#include "Info.h"
#include "Input.h"
#include "PageBase.h"
#include "Renderer.h"

import std;

void PlayingPage::onEnter(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();

	engine.reset();
	renderer.drawMapWall(map);
	renderer.drawMapInnerCells(map);
	renderer.drawStartMessage();
}

void PlayingPage::onExit(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();

	renderer.clearMapInnerCells(map);
	renderer.clearBelowMapText();
	renderer.clearMapWall(map);
}

std::unique_ptr<PageBase> PlayingPage::run(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();
	auto& info = engine.info();

	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 's': case 'S':
			engine.start();
			renderer.drawMapInnerCells(map);
			renderer.drawActiveInfo(info);

			mainLoop(ctx);

			switch (GameStatus status = info.status()) {
			case GameStatus::Quit:
				return std::make_unique<EnteringPage>();
			default:
				renderer.drawOverAnimation(map, status);
			}

			renderer.drawOverInfo(info);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			Input::flush();

			while (true) {
				switch (Input::waitKey()) {
				case 'e': case 'E':
					return std::make_unique<PlayingPage>();
				case 'q': case 'Q':
					return std::make_unique<EnteringPage>();
				}
			}

			break;
		case 'q': case 'Q':
			return std::make_unique<EnteringPage>();
		}
	}
}

void PlayingPage::mainLoop(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();
	auto& info = engine.info();

	namespace ch = std::chrono;

	//获取常规更新时间间隔
	auto normalInterval = [&]() -> ch::steady_clock::duration {
		return ch::milliseconds(1'000'000 / info.speed());
	};

	GameStatus lastStatus = info.status();
	auto lastUpdate = ch::steady_clock::now();
	auto interval = normalInterval() / 2;

	while (true) {
		std::this_thread::sleep_for(ch::milliseconds(5));

		//处理按键输入
		while (auto key = Input::pullKey()) {
			if (auto cmd = toGameCommand(*key)) {
				engine.handleCommand(*cmd);
			}
		}

		//处理游戏状态
		switch (GameStatus status = info.status()) {
		case GameStatus::Active:
			if (status != lastStatus) {
				renderer.drawActiveInfo(info);
				lastUpdate = ch::steady_clock::now();
				interval = normalInterval() / 2;
				lastStatus = status;
			}
			break;
		case GameStatus::Pause:
			if (status != lastStatus) {
				renderer.drawPauseInfo(info);
				lastStatus = status;
			}
			continue;
		default:
			return;
		}

		//处理游戏逻辑和画面渲染
		if (auto now = ch::steady_clock::now(); now - lastUpdate >= interval) {
			engine.update();
			//将上次更新时间点后移，而不直接设为当前时间，可消除累计误差，提高稳定性
			lastUpdate += interval;
			interval = normalInterval();
			//若落后过长时间则暂时停止渲染，优先保证游戏进程正常前进
			if (now - lastUpdate < interval) {
				renderer.drawMapInnerCells(map);
				renderer.drawActiveInfo(info);
			}
		}
	}
}

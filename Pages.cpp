//Pages.cpp
#include "Pages.h"

#include "Console.h"
#include "GameCommand.h"
#include "GameEngine.h"
#include "Info.h"
#include "Input.h"
#include "PageBase.h"
#include "Renderer.h"

import std;

std::unique_ptr<PageBase> EnterPage::run(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	renderer.drawEnterMessage();
	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 'e': case 'E':
			renderer.clearEnterMessage();
			return std::make_unique<StartingPage>();
		case 'r': case 'R':
			renderer.clearEnterMessage();
			return std::make_unique<SettingsPage>();
		case 'q': case 'Q':
			renderer.drawConfirmExitMessage();

			switch (Input::waitKey()) {
			case 'q': case 'Q':
				renderer.clearEnterMessage();
				return nullptr;
			}

			renderer.redrawEnterMessage();
			break;
		case ' ':
			switch (int key = Input::waitKey()) {
			case ' ':
				Console::clear();
				return std::make_unique<EnterPage>();
			default:
				Input::pushKey(key);
			}

			break;
		}
	}
}

std::unique_ptr<PageBase> StartingPage::run(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();

	engine.reset();
	renderer.drawMapWall(map);
	renderer.drawMapInnerCells(map);
	renderer.drawStartMessage();
	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 's': case 'S':
			return std::make_unique<PlayPage>();
		case 'q': case 'Q':
			renderer.clearMapInnerCells(map);
			renderer.clearBelowMapText();
			renderer.clearMapWall(map);
			return std::make_unique<EnterPage>();
		}
	}
}

std::unique_ptr<PageBase> PlayPage::run(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();
	auto& info = engine.info();

	mainLoop(ctx);

	//按顺序清除整个页面内容
	auto clearPage = [&]() {
		renderer.clearMapInnerCells(map);
		renderer.clearBelowMapText();
		renderer.clearMapWall(map);
	};

	switch (GameStatus status = info.status()) {
	case GameStatus::Quit:
		//若为中途退出，则直接返回上一页，不再显示结束信息
		clearPage();
		return std::make_unique<EnterPage>();
	default:
		renderer.drawOverAnimation(map, status);
	}

	renderer.drawOverInfo(info);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 'e': case 'E':
			clearPage();
			return std::make_unique<StartingPage>();
		case 'q': case 'Q':
			clearPage();
			return std::make_unique<EnterPage>();
		}
	}
}

void PlayPage::mainLoop(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& map = engine.map();
	auto& info = engine.info();

	engine.start();
	renderer.drawMapInnerCells(map);
	renderer.drawActiveInfo(info);

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
			//二次检测，避免落后过长时间导致暴力追赶
			if (now - lastUpdate >= interval) {
				lastUpdate = ch::steady_clock::now();
			}
			else {
				renderer.drawMapInnerCells(map);
				renderer.drawActiveInfo(info);
			}
		}
	}
}

std::unique_ptr<PageBase> SettingsPage::run(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& settings = engine.settings();

	renderer.drawSettings(settings);
	size_t nowItem = 0;
	renderer.redrawSettings(settings, nowItem);

	std::vector<std::function<void()>> toggleSetting = {
		[&]() { settings.toggleIsMoreFood(); },
		[&]() { settings.toggleIsUnbounded(); },
		[&]() { settings.toggleCanPause(); },
		[&]() { settings.toggleIsInvincible(); },
	};

	while (true) {
		//每次循环中，适当延时并刷新键盘缓冲区后重新读取按键，避免用户高频操作
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		Input::flush();

		switch (Input::waitKey()) {
		case 'w': case 'W':
			nowItem = (nowItem + toggleSetting.size() - 1) % toggleSetting.size();
			break;
		case 's': case 'S':
			nowItem = (nowItem + 1) % toggleSetting.size();
			break;
		case 'a': case 'A':
		case 'd': case 'D':
			toggleSetting[nowItem]();
			break;
		case 'q': case 'Q':
			renderer.clearSettings();
			return std::make_unique<EnterPage>();
		default:
			continue;
		}

		renderer.redrawSettings(settings, nowItem);
	}
}

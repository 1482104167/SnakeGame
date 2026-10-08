//Game.cpp
#include "Game.h"

#include "Console.h"
#include "GameCommand.h"
#include "Info.h"
#include "Input.h"
#include "Renderer.h"
#include "Settings.h"
#include "SysTimerRes.h"

import std;

void Game::run() {
	//提高系统计时器分辨率，使 sleep 延时更精确
	SysTimerRes timerRes(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	PageNav page = PageNav::Enter;
	while (true) {
		switch (page) {
		case PageNav::Enter:	page = showEnterPage();		break;
		case PageNav::Start:	page = showStartPage();		break;
		case PageNav::Play:		page = showPlayPage();		break;
		case PageNav::Settings: page = showSettingsPage();	break;
		case PageNav::Exit:		return;
		}
	}
}

Game::PageNav Game::showEnterPage() {
	renderer_.drawEnterMessage();
	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 'e': case 'E':
			renderer_.clearEnterMessage();
			return PageNav::Start;
		case 'r': case 'R':
			renderer_.clearEnterMessage();
			return PageNav::Settings;
		case 'q': case 'Q':
			renderer_.drawConfirmExitMessage();

			switch (Input::waitKey()) {
			case 'q': case 'Q':
				return PageNav::Exit;
			}

			renderer_.redrawEnterMessage();
			break;
		case ' ':
			switch (int key = Input::waitKey()) {
			case ' ':
				Console::clear();
				return PageNav::Enter;
			default:
				Input::pushKey(key);
			}

			break;
		}
	}
}

Game::PageNav Game::showStartPage() {
	auto& map = engine_.map();

	engine_.reset();
	renderer_.drawMapWall(map);
	renderer_.drawMapInnerCells(map);
	renderer_.drawStartMessage();
	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 's': case 'S':
			return PageNav::Play;
		case 'q': case 'Q':
			renderer_.clearMapInnerCells(map);
			renderer_.clearBelowMapText();
			renderer_.clearMapWall(map);
			return PageNav::Enter;
		}
	}
}

Game::PageNav Game::showPlayPage() {
	auto& map = engine_.map();
	auto& info = engine_.info();

	mainLoop();

	//按顺序清除整个页面内容
	auto clearPage = [&]() {
		renderer_.clearMapInnerCells(map);
		renderer_.clearBelowMapText();
		renderer_.clearMapWall(map);
	};

	switch (GameStatus status = info.status()) {
	case GameStatus::Quit:
		//若为中途退出，则直接返回上一页，不再显示结束信息
		clearPage();
		return PageNav::Enter;
	default:
		renderer_.drawOverAnimation(map, status);
	}

	renderer_.drawOverInfo(info);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 'e': case 'E':
			clearPage();
			return PageNav::Start;
		case 'q': case 'Q':
			clearPage();
			return PageNav::Enter;
		}
	}
}

Game::PageNav Game::showSettingsPage() {
	auto& settings = engine_.settings();

	renderer_.drawSettings(settings);
	size_t nowItem = 0;
	renderer_.redrawSettings(settings, nowItem);

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
			renderer_.clearSettings();
			return PageNav::Enter;
		default:
			continue;
		}

		renderer_.redrawSettings(settings, nowItem);
	}
}

void Game::mainLoop() {
	auto& map = engine_.map();
	auto& info = engine_.info();

	engine_.start();
	renderer_.drawMapInnerCells(map);
	renderer_.drawActiveInfo(info);

	namespace ch = std::chrono;

	auto normalInterval = [&]() -> ch::steady_clock::duration {
		return ch::milliseconds(1'000'000 / info.speed());
	};

	GameStatus lastStatus = info.status();
	ch::steady_clock::time_point lastUpdate = ch::steady_clock::now();
	ch::steady_clock::duration interval = normalInterval() / 2;

	while (true) {
		std::this_thread::sleep_for(ch::milliseconds(5));

		//处理按键输入
		while (auto key = Input::pullKey()) {
			if (auto cmd = toGameCommand(*key)) {
				engine_.handleCommand(*cmd);
			}
		}

		//处理游戏状态
		switch (GameStatus status = info.status()) {
		case GameStatus::Active:
			if (status != lastStatus) {
				renderer_.drawActiveInfo(info);
				lastUpdate = ch::steady_clock::now();
				interval = normalInterval() / 2;
				lastStatus = status;
			}
			break;
		case GameStatus::Pause:
			if (status != lastStatus) {
				renderer_.drawPauseInfo(info);
				lastStatus = status;
			}
			continue;
		default:
			return;
		}

		//处理游戏逻辑和画面渲染
		if (auto now = ch::steady_clock::now(); now - lastUpdate >= interval) {
			engine_.update();
			renderer_.drawMapInnerCells(map);
			renderer_.drawActiveInfo(info);
			//将上次更新时间点后移，而不直接设为当前时间，可消除累计误差，提高稳定性
			lastUpdate += interval;
			interval = normalInterval();
			//二次检测，避免落后过长时间导致暴力追赶
			if (now - lastUpdate >= interval) {
				lastUpdate = ch::steady_clock::now();
			}
		}
	}
}

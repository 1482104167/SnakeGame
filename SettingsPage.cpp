//SettingsPage.cpp
#include "SettingsPage.h"

#include "EnteringPage.h"
#include "GameEngine.h"
#include "Input.h"
#include "PageBase.h"
#include "Renderer.h"

import std;

void SettingsPage::onEnter(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& settings = engine.settings();

	renderer.drawSettings(settings);
}

void SettingsPage::onExit(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	renderer.clearSettings();
}

std::unique_ptr<PageBase> SettingsPage::run(GameContext& ctx) {
	auto& engine = ctx.engine;
	auto& renderer = ctx.renderer;
	auto& settings = engine.settings();

	size_t nowItem = 0;
	renderer.redrawSettings(settings, nowItem);

	std::vector<std::function<void()>> toggleSetting = {
		[&]() { settings.toggleIsNoRedFood(); },
		[&]() { settings.toggleIsUnbounded(); },
		[&]() { settings.toggleIsAllowPause(); },
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
			return std::make_unique<EnteringPage>();
		default:
			continue;
		}

		renderer.redrawSettings(settings, nowItem);
	}
}

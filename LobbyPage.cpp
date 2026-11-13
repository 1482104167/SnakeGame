//LobbyPage.cpp
#include "LobbyPage.h"

#include "Console.h"
#include "Input.h"
#include "PageBase.h"
#include "PlayPage.h"
#include "Renderer.h"
#include "SettingsPage.h"

import std;

void LobbyPage::onEnter(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	renderer.drawEnterMessage();
}

void LobbyPage::onExit(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	renderer.clearEnterMessage();
}

std::unique_ptr<PageBase> LobbyPage::run(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 'e': case 'E':
			return std::make_unique<PlayPage>();
		case 'r': case 'R':
			return std::make_unique<SettingsPage>();
		case 'q': case 'Q':
			renderer.drawConfirmExitMessage();

			switch (Input::waitKey()) {
			case 'q': case 'Q':
				return nullptr;
			}

			renderer.redrawEnterMessage();
			break;
		case ' ':
			switch (int key = Input::waitKey()) {
			case ' ':
				Console::clear();
				return std::make_unique<LobbyPage>();
			default:
				Input::pushKey(key);
			}

			break;
		}
	}
}

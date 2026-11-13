//EnteringPage.cpp
#include "EnteringPage.h"

#include "Console.h"
#include "Input.h"
#include "PageBase.h"
#include "PlayingPage.h"
#include "Renderer.h"
#include "SettingsPage.h"

import std;

void EnteringPage::onEnter(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	renderer.drawEnterMessage();
}

void EnteringPage::onExit(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	renderer.clearEnterMessage();
}

std::unique_ptr<PageBase> EnteringPage::run(GameContext& ctx) {
	auto& renderer = ctx.renderer;

	Input::flush();

	while (true) {
		switch (Input::waitKey()) {
		case 'e': case 'E':
			return std::make_unique<PlayingPage>();
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
				return std::make_unique<EnteringPage>();
			default:
				Input::pushKey(key);
			}

			break;
		}
	}
}

//SettingsPage.h
#pragma once

#include "PageBase.h"
#include <memory>

class SettingsPage : public PageBase {
public:
	void onEnter(GameContext& ctx) override;
	void onExit(GameContext& ctx) override;
	std::unique_ptr<PageBase> run(GameContext& ctx) override;
};

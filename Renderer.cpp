//Renderer.cpp
#include "Renderer.h"

#include "Console.h"
#include "Info.h"
#include "Map.h"
#include "Point.h"
#include "Settings.h"

import std;

void Renderer::drawMapWall(const Map& map) const {
	Console::setTextColor(Color::White);

	int mx = map.cols - 1;
	int my = map.rows - 1;
	Point off = defaultOff;

	for (int y = 0; y <= my; ++y) {
		drawMapHelper(Point(0, y), off, Map::CellType::Wall);
		drawMapHelper(Point(mx, my - y), off, Map::CellType::Wall);
		std::this_thread::sleep_for(mapDelay);
	}
	for (int x = 1; x <= mx - 1; ++x) {
		drawMapHelper(Point(mx - x, 0), off, Map::CellType::Wall);
		drawMapHelper(Point(x, my), off, Map::CellType::Wall);
		std::this_thread::sleep_for(mapDelay);
	}
}

void Renderer::clearMapWall(const Map& map) const {
	int mx = map.cols - 1;
	int my = map.rows - 1;
	Point off = defaultOff;

	for (int y = 0; y <= my; ++y) {
		drawMapHelper(Point(0, y), off, Map::CellType::Empty);
		drawMapHelper(Point(mx, my - y), off, Map::CellType::Empty);
		std::this_thread::sleep_for(mapDelay);
	}
	for (int x = 1; x <= mx - 1; ++x) {
		drawMapHelper(Point(mx - x, 0), off, Map::CellType::Empty);
		drawMapHelper(Point(x, my), off, Map::CellType::Empty);
		std::this_thread::sleep_for(mapDelay);
	}
}

void Renderer::drawMapInnerCells(const Map& map) const {
	for (int y = 1; y < map.rows - 1; ++y) {
		for (int x = 1; x < map.cols - 1; ++x) {
			Point pos = Point(x, y);
			drawMapHelper(pos, defaultOff, map.get(pos));
		}
	}
}

void Renderer::clearMapInnerCells(const Map& map) const {
	clearRectArea(defaultOff + Point(2, 1), 2 * map.cols - 5, map.rows - 2);
}

void Renderer::drawOverAnimation(const Map& map, GameStatus status) const {
	switch (status) {
	case GameStatus::Lose:	Console::setTextColor(loseColor);	break;
	case GameStatus::Win:	Console::setTextColor(winColor);	break;
	default: return;
	}

	int mx = map.cols - 1;
	int my = map.rows - 1;
	Point off = defaultOff;

	for (int y = 0; y <= my; y += 2) {
		drawMapHelper(Point(0, y), off, Map::CellType::Wall);
		drawMapHelper(Point(mx, my - y), off, Map::CellType::Wall);
	}
	for (int x = 1; x <= mx - 1; x += 2) {
		drawMapHelper(Point(mx - x, 0), off, Map::CellType::Wall);
		drawMapHelper(Point(x, my), off, Map::CellType::Wall);
	}
}

void Renderer::drawEnterMessage() const {
	Point printPos = defaultOff;

	std::vector<std::string> text = {
		"贪吃蛇游戏",
		"ver: 2026.10.9",
		"",
		"* 为避免输入法按键冲突，建议开启大写锁定",
		"* 若出现显示错误，可尝试双击空格刷新页面",
	};

	Console::setTextColor(defaultColor);
	for (std::string_view lineText : text) {
		Console::setCursorPos(printPos);
		printCenter(lineText);
		std::this_thread::sleep_for(textDelay);
		printPos += Point(0, 1);
	}

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos += Point(0, 1));
	printCenter("[E] 进入游戏   [R] 进入设置   [Q] 退出程序");
}

void Renderer::redrawEnterMessage() const {
	Point printPos = defaultOff;

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos += Point(0, 6));
	printCenter("[E] 进入游戏   [R] 进入设置   [Q] 退出程序");
}

void Renderer::drawConfirmExitMessage() const {
	Point printPos = defaultOff;

	Console::setTextColor(confirmColor);
	Console::setCursorPos(printPos += Point(0, 6));
	printCenter("[Q] 退出程序");
}

void Renderer::clearEnterMessage() const {
	clearRectArea(defaultOff, windowWidth, 7, textDelay);
}

void Renderer::drawStartMessage() const {
	Point printPos = belowMapTextOff;

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos);
	printCenter("[S] 开始游戏    [Q] 返回上一页");
}

void Renderer::drawActiveInfo(const Info& info) const {
	Point printPos = belowMapTextOff;

	Console::setTextColor(defaultColor);
	Console::setCursorPos(printPos);
	printCenter(std::format("当前得分 {:<4}", info.score()));

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos += Point(0, 2));
	printCenter("[W][A][S][D] 移动    [Esc] 退出游戏");
}

void Renderer::drawPauseInfo(const Info& info) const {
	Point printPos = belowMapTextOff;

	Console::setTextColor(defaultColor);
	Console::setCursorPos(printPos);
	printCenter(std::format("当前得分 {:<4}", info.score()));

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos += Point(0, 2));
	printCenter("[空格] 继续游戏    [Esc] 退出游戏");
}

void Renderer::drawOverInfo(const Info& info) const {
	Point printPos = belowMapTextOff;

	Console::setTextColor(defaultColor);
	Console::setCursorPos(printPos);
	printCenter(std::format("最终得分 {:<4}", info.score()));

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos += Point(0, 2));
	printCenter("[E] 重新开始    [Q] 返回上一页");
}

void Renderer::clearBelowMapText() const {
	clearRectArea(belowMapTextOff, windowWidth, 3);
}

void Renderer::drawSettings(const Settings& settings) const {
	std::vector<std::string> text = {
		"设置",
		"",
		formatSettingItem("额外生成食物", settings.isMoreFood()),
		formatSettingItem("无界模式", settings.isUnbounded()),
		formatSettingItem("游戏中可暂停", settings.canPause()),
		formatSettingItem("无敌模式", settings.isInvincible()),
		"",
	};

	Point printPos = defaultOff;

	Console::setTextColor(defaultColor);
	for (std::string_view lineText : text) {
		Console::setCursorPos(printPos);
		printPos += Point(0, 1);
		printCenter(lineText);
		std::this_thread::sleep_for(textDelay);
	}

	Console::setTextColor(promptColor);
	Console::setCursorPos(printPos);
	printCenter("[W][A][S][D] 选择和切换设置    [Q] 返回上一页");
}

void Renderer::redrawSettings(const Settings& settings, size_t item) const {
	std::vector<std::tuple<Point<int>, std::string>> textInfo = {
		std::make_tuple(Point(0, 2),
			formatSettingItem("额外生成食物", settings.isMoreFood())),
		std::make_tuple(Point(0, 1),
			formatSettingItem("无界模式", settings.isUnbounded())),
		std::make_tuple(Point(0, 1),
			formatSettingItem("游戏中可暂停", settings.canPause())),
		std::make_tuple(Point(0, 1),
			formatSettingItem("无敌模式", settings.isInvincible())),
	};

	Point printPos = defaultOff;
	for (size_t i = 0; i < textInfo.size(); ++i) {
		Console::setTextColor((i == item) ? selectedColor : defaultColor);
		const auto& [relPos, text] = textInfo[i];
		Console::setCursorPos(printPos += relPos);
		printCenter(text);
	}
}

void Renderer::clearSettings() const {
	clearRectArea(defaultOff, windowWidth, 8, textDelay);
}

void Renderer::drawMapHelper(Point<int> pos, Point<int> off,
	Map::CellType type) const {
	Console::setCursorPos(pos * Point(2, 1) + off);

	switch (type) {
	case Map::CellType::Empty:
		std::print(" ");
		break;
	case Map::CellType::Wall:
		std::print("#");
		break;
	case Map::CellType::SnakeHead:
		Console::setTextColor(Color::BrightGreen);
		std::print("@");
		break;
	case Map::CellType::SnakeBody:
		Console::setTextColor(Color::BrightYellow);
		std::print("O");
		break;
	case Map::CellType::SnakeTail:
		Console::setTextColor(Color::White);
		std::print("O");
		break;
	case Map::CellType::Food:
		Console::setTextColor(Color::Yellow);
		std::print("*");
		break;
	case Map::CellType::RedFood:
		Console::setTextColor(Color::BrightRed);
		std::print("*");
		break;
	}
}

void Renderer::clearRectArea(Point<int> topLeft, int width, int height,
	Duration lineDelay) const {
	if (width <= 0 || height <= 0) {
		return;
	}

	std::string spaces(width, ' ');
	for (int i = 0; i < height; ++i) {
		Console::setCursorPos(topLeft);
		std::print("{}", spaces);
		std::this_thread::sleep_for(lineDelay);
		topLeft += Point(0, 1);
	}
}

void Renderer::printCenter(std::string_view text) const {
	std::print("{:^{}}", text, windowWidth);
}

std::string Renderer::formatSettingItem(std::string_view title, bool option) const {
	return std::format("{:<14} < {:<3} >", title, (option ? "ON" : "OFF"));
}

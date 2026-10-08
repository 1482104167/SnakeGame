//Renderer.h
#pragma once

#include "Console.h"
#include "Info.h"
#include "Map.h"
#include "Point.h"
#include "Settings.h"
#include <chrono>
#include <string>
#include <string_view>

class Renderer {
public:
	//绘制地图墙体
	void drawMapWall(const Map& map) const;
	//清除地图墙体
	void clearMapWall(const Map& map) const;
	//绘制地图内部格子
	void drawMapInnerCells(const Map& map) const;
	//清除地图内部格子
	void clearMapInnerCells(const Map& map) const;
	//绘制结束动画
	void drawOverAnimation(const Map& map, GameStatus status) const;

	//绘制进入提示
	void drawEnterMessage() const;
	//重绘进入提示
	void redrawEnterMessage() const;
	//绘制确认退出提示
	void drawConfirmExitMessage() const;
	//清除进入提示
	void clearEnterMessage() const;

	//绘制开始提示
	void drawStartMessage() const;
	//绘制进行信息
	void drawActiveInfo(const Info& info) const;
	//绘制暂停信息
	void drawPauseInfo(const Info& info) const;
	//绘制结束信息
	void drawOverInfo(const Info& info) const;
	//清除地图下方文本
	void clearBelowMapText() const;

	//绘制设置
	void drawSettings(const Settings& settings) const;
	//重绘设置
	void redrawSettings(const Settings& settings, size_t item) const;
	//清除设置
	void clearSettings() const;

private:
	//类型别名
	using Duration = std::chrono::steady_clock::duration;

	//位置偏移
	static constexpr Point defaultOff = Point(1, 0);
	static constexpr Point belowMapTextOff = Point(1, Map::rows + 1);

	//动画延时
	static constexpr Duration mapDelay = std::chrono::milliseconds(13);
	static constexpr Duration textDelay = std::chrono::milliseconds(48);

	//文本颜色
	static constexpr Color defaultColor = Color::White;
	static constexpr Color promptColor = Color::Cyan;
	static constexpr Color confirmColor = Color::BrightRed;
	static constexpr Color loseColor = Color::BrightRed;
	static constexpr Color winColor = Color::BrightGreen;
	static constexpr Color selectedColor = Color::Yellow;

	//窗口宽度
	static constexpr int windowWidth = 47;

	//辅助绘制地图函数
	void drawMapHelper(Point<int> pos, Point<int> off, Map::CellType type) const;
	//清空矩形区域
	void clearRectArea(Point<int> topLeft, int width, int height,
		Duration lineDelay = std::chrono::seconds(0)) const;
	//居中打印文本
	void printCenter(std::string_view text) const;
	//格式化设置项文本
	std::string formatSettingItem(std::string_view title, bool option) const;
};

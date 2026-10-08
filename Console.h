//Console.h
#pragma once

#include "Point.h"
#include <Windows.h>

//控制台输出文本颜色（背景色默认为黑色）
enum class Color : WORD {
	Black, Blue, Green, Cyan, Red, Purple, Yellow,
	White, Grey, BrightBlue, BrightGreen, BrightCyan,
	BrightRed, BrightPurple, BrightYellow, BrightWhite
};

class Console {
public:
	//禁用默认构造
	Console() = delete;

	//清屏
	static void clear();
	//设置光标可见性
	static void setCursorVis(bool visible);
	//设置光标位置
	static void setCursorPos(Point<int> pos);
	//设置文本颜色
	static void setTextColor(Color color);
	//获取窗口大小
	static Point<int> getWindowSize();

private:
	static inline HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
};

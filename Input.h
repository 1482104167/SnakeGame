//Input.h
#pragma once

#include <optional>

class Input {
public:
	//禁用默认构造
	Input() = delete;

	//非阻塞读取一个按键（无按键时返回空）
	static std::optional<int> pullKey();
	//阻塞读取一个按键
	static int waitKey();
	//向缓冲区写入一个按键
	static void pushKey(int key);
	//刷新按键缓冲区
	static void flush();
};

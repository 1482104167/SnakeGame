//Snake.h
#pragma once

#include "Point.h"
#include <queue>

//方向
enum class Direction : unsigned char {
	Up, Left, Down, Right
};

class Snake {
public:
	//蛇体初始长度
	static constexpr int initLength = 3;

	//默认构造函数
	Snake() = default;

	//禁用拷贝构造和赋值
	Snake(const Snake&) = delete;
	Snake& operator=(const Snake&) = delete;

	//默认移动构造和赋值
	Snake(Snake&&) noexcept = default;
	Snake& operator=(Snake&&) noexcept = default;

	//重置数据
	void reset();
	//获取当前蛇体长度
	int length() const;
	//获取当前蛇头坐标
	Point<int> head() const;
	//获取当前蛇尾坐标
	Point<int> tail() const;
	//获取下一帧蛇头坐标
	Point<int> nextHead() const;
	//增加蛇头
	void addHead(Point<int> nextHead);
	//删除蛇尾
	void delTail();
	//新方向尝试加入待处理队列
	void pushPendingDirs(Direction newDir);
	//清空待处理方向队列
	void clearPendingDirs();
	//应用下一有效方向
	void applyNextDir();

private:
	//待处理方向队列最大长度（允许缓存一定数量方向，优化操作手感）
	static constexpr size_t pendingDirsMaxSize = 3;

	std::queue<Point<int>> snake_;
	std::queue<Direction> pendingDirs_;
	Direction dir_ = Direction::Up;
};

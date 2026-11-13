//Snake.cpp
#include "Snake.h"

#include "Point.h"

import std;

void Snake::reset() {
	snake_.clear();
	clearPendingDirs();
	dir_ = Direction::Up;
}

int Snake::length() const {
	return static_cast<int>(snake_.size());
}

Point<int> Snake::head() const {
	if (!snake_.empty()) {
		return snake_.front();
	}
	return Point(0, 0);
}

Point<int> Snake::tail() const {
	if (!snake_.empty()) {
		return snake_.back();
	}
	return Point(0, 0);
}

Point<int> Snake::nextHead() const {
	int dx = 0;
	int dy = 0;

	switch (dir_) {
	case Direction::Up:		--dy; break;
	case Direction::Left:	--dx; break;
	case Direction::Down:	++dy; break;
	case Direction::Right:	++dx; break;
	}

	return head() + Point(dx, dy);
}

void Snake::addHead(Point<int> nextHead) {
	snake_.push_front(nextHead);
}

void Snake::delTail() {
	if (!snake_.empty()) {
		snake_.pop_back();
	}
}

void Snake::pushPendingDirs(Direction newDir) {
	Direction lastDir = pendingDirs_.empty() ? dir_ : pendingDirs_.back();

	//拦截相同或相反的方向
	auto isOpposite = [](Direction dir1, Direction dir2) {
		using enum Direction;
		return (dir1 == Up && dir2 == Down) || (dir1 == Down && dir2 == Up) ||
			(dir1 == Left && dir2 == Right) || (dir1 == Right && dir2 == Left);
	};

	if (newDir == lastDir || isOpposite(newDir, lastDir)) { return; }

	if (pendingDirs_.size() < pendingDirsMaxSize) {
		pendingDirs_.push(newDir);
	}
}

void Snake::clearPendingDirs() {
	pendingDirs_ = {};
}

void Snake::applyNextDir() {
	if (!pendingDirs_.empty()) {
		dir_ = pendingDirs_.front();
		pendingDirs_.pop();
	}
}

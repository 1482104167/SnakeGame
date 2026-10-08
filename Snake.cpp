//Snake.cpp
#include "Snake.h"

#include "Point.h"

void Snake::reset() {
	*this = Snake();
}

int Snake::length() const {
	return static_cast<int>(snake_.size());
}

Point<int> Snake::head() const {
	//注意队尾代表蛇头，队首代表蛇尾，下同
	if (!snake_.empty()) {
		return snake_.back();
	}
	return Point(0, 0);
}

Point<int> Snake::tail() const {
	if (!snake_.empty()) {
		return snake_.front();
	}
	return Point(0, 0);
}

Point<int> Snake::nextHead() const {
	Point result = head();

	switch (dir_) {
	case Direction::Up:		--result.y; break;
	case Direction::Left:	--result.x; break;
	case Direction::Down:	++result.y; break;
	case Direction::Right:	++result.x; break;
	}

	return result;
}

void Snake::addHead(Point<int> nextHead) {
	snake_.push(nextHead);
}

void Snake::delTail() {
	if (!snake_.empty()) {
		snake_.pop();
	}
}

void Snake::pushPendingDirs(Direction newDir) {
	auto isOpposite = [](Direction dir1, Direction dir2) {
		using enum Direction;
		return (dir1 == Up && dir2 == Down) || (dir1 == Down && dir2 == Up) ||
			(dir1 == Left && dir2 == Right) || (dir1 == Right && dir2 == Left);
	};

	Direction lastDir = pendingDirs_.empty() ? dir_ : pendingDirs_.back();
	//拦截相同或相反的方向
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

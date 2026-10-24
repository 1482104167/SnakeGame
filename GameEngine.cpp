//GameEngine.cpp
#include "GameEngine.h"

#include "GameCommand.h"
#include "Info.h"
#include "Map.h"
#include "Point.h"
#include "Settings.h"
#include "Snake.h"
#include "Utils.h"

import std;

void GameEngine::reset() {
	map_.reset();
	snake_.reset();
	info_.reset();

	//设置蛇体和地图
	for (int node = snake_.initLength - 1; node >= 0; --node) {
		snake_.addHead(Point((map_.cols - 1) / 2, (map_.rows - 1) / 2 + node));
		map_.set(snake_.head(), Map::CellType::SnakeBody);
	}

	map_.set(snake_.tail(), Map::CellType::SnakeTail);
	map_.set(snake_.head(), Map::CellType::SnakeHead);

	moreFoodCounter_ = 0;
	moreFoodThreshold_ = 0;
}

void GameEngine::start() {
	info_.setStatus(GameStatus::Active);
	map_.generate(Map::CellType::Food);
}

void GameEngine::update() {
	snake_.applyNextDir();

	//实现多食物设置
	auto realizeMoreFood = [this]() {
		if (!settings_.isMoreFood()) { return; }

		//蛇达到一定长度后，才开始生成红色食物（第一次达到时会立即生成）
		if (snake_.length() - snake_.initLength < 15) { return; }

		//生成计数器自增，并检测是否达到阈值
		if (++moreFoodCounter_ < moreFoodThreshold_) { return; }

		//生成成功，重置计数器，并重新随机指定新阈值
		map_.generate(Map::CellType::RedFood);
		moreFoodCounter_ = 0;
		moreFoodThreshold_ = utils::getRandom(50, 150);
	};

	Point nextHead = snake_.nextHead();

	//实现无界设置
	if (settings_.isUnbounded()) {
		auto& [x, y] = nextHead;
		if (x == 0) { x = map_.cols - 2; }
		else if (x == map_.cols - 1) { x = 1; }
		else if (y == 0) { y = map_.rows - 2; }
		else if (y == map_.rows - 1) { y = 1; }
	}

	switch (map_.get(nextHead)) {
	case Map::CellType::Wall:
	case Map::CellType::SnakeBody:
		//实现无敌设置
		if (!settings_.isInvincible()) {
			info_.setStatus(GameStatus::Lose);
		}
		break;
	case Map::CellType::Empty:
	case Map::CellType::SnakeTail:
		//更新蛇体和地图上相应元素（顺序不应改变，否则可能导致逻辑错误）
		map_.set(snake_.head(), Map::CellType::SnakeBody);
		map_.set(snake_.tail(), Map::CellType::Empty);
		snake_.delTail();
		snake_.addHead(nextHead);
		map_.set(snake_.tail(), Map::CellType::SnakeTail);
		map_.set(snake_.head(), Map::CellType::SnakeHead);

		realizeMoreFood();
		break;
	case Map::CellType::Food:
		map_.generate(Map::CellType::Food);
		[[fallthrough]];
	case Map::CellType::RedFood:
		//更新蛇体和地图上相应元素（顺序不应改变，否则可能导致逻辑错误）
		map_.set(snake_.head(), Map::CellType::SnakeBody);
		snake_.addHead(nextHead);
		map_.set(snake_.tail(), Map::CellType::SnakeTail);
		map_.set(snake_.head(), Map::CellType::SnakeHead);

		info_.increaseScore();

		//判断游戏是否胜利（蛇是否占满所有格子）
		if (snake_.length() >= map_.innerCellNum) {
			info_.setStatus(GameStatus::Win);
			break;
		}

		info_.increaseSpeed();
		realizeMoreFood();
		break;
	default:
		info_.setStatus(GameStatus::Idle);
	}
}

void GameEngine::handleCommand(GameCommand cmd) {
	switch (cmd) {
	case GameCommand::Up:		snake_.pushPendingDirs(Direction::Up);		break;
	case GameCommand::Down:		snake_.pushPendingDirs(Direction::Down);	break;
	case GameCommand::Left:		snake_.pushPendingDirs(Direction::Left);	break;
	case GameCommand::Right:	snake_.pushPendingDirs(Direction::Right);	break;

	case GameCommand::TogglePause:
		//实现暂停设置
		if (!settings_.canPause()) { break; }

		switch (info_.status()) {
		case GameStatus::Active:
			info_.setStatus(GameStatus::Pause);
			break;
		case GameStatus::Pause:
			info_.setStatus(GameStatus::Active);
			//继续游戏后清空待处理方向，避免暂停前的转向被延迟执行
			snake_.clearPendingDirs();
			break;
		}

		break;
	case GameCommand::Quit:
		info_.setStatus(GameStatus::Quit);
		break;
	}
}

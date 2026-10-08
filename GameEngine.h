//GameEngine.h
#pragma once

#include "GameCommand.h"
#include "Info.h"
#include "Map.h"
#include "Settings.h"
#include "Snake.h"

class GameEngine {
public:
	//重置游戏数据
	void reset();
	//开始游戏
	void start();
	//更新一帧游戏逻辑
	void update();
	//处理指定游戏命令
	void handleCommand(GameCommand cmd);

	//公共访问接口
	Map& map() { return map_; }
	Snake& snake() { return snake_; }
	Info& info() { return info_; }
	Settings& settings() { return settings_; }

private:
	Map map_;
	Snake snake_;
	Info info_;
	Settings settings_;
};
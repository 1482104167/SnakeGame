//PageBase.h
#pragma once

#include <memory>

class GameEngine;
class Renderer;

//上下文依赖
struct GameContext {
	GameEngine& engine;
	Renderer& renderer;
};

//页面基类
class PageBase {
public:
	//默认虚析构函数
	virtual ~PageBase() = default;

	//进入页面时操作
	virtual void onEnter(GameContext& ctx) = 0;
	//运行页面，并返回下一页面状态（返回 nullptr 表示退出程序）
	virtual std::unique_ptr<PageBase> run(GameContext& ctx) = 0;
	//退出页面时操作
	virtual void onExit(GameContext& ctx) = 0;
};

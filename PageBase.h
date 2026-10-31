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

	//运行页面，并返回下一页面状态（返回 nullptr 表示退出）
	virtual std::unique_ptr<PageBase> run(GameContext& ctx) = 0;
};
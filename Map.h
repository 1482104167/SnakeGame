//Map.h
#pragma once

#include "Point.h"
#include <vector>

class Map {
public:
	//地图单元格类型
	enum class CellType : unsigned char {
		Empty, Wall, SnakeHead, SnakeBody, SnakeTail, Food, RedFood
	};

	//地图列数，行数，内部单元格数
	static constexpr int cols = 24;
	static constexpr int rows = 20;
	static constexpr int innerCellNum = (cols - 2) * (rows - 2);

	//构造函数：给地图数组预留内存空间
	Map();

	//重置数据：清空地图并重新设置墙体
	void reset();
	//获取指定坐标单元格类型
	CellType get(Point<int> pos) const;
	//设置指定坐标单元格类型
	void set(Point<int> pos, CellType type);
	//随机生成食物
	void generate(CellType foodType);

private:
	std::vector<CellType> map_;
};

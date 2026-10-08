//Map.cpp
#include "Map.h"

#include "Point.h"
#include "Utils.h"

import std;

Map::Map() {
	map_.reserve(cols * rows);
	map_.assign(cols * rows, CellType::Empty);
}

void Map::reset() {
	//设置墙体
	for (int x = 0; x < cols; ++x) {
		set(Point(x, 0), CellType::Wall);
		set(Point(x, rows - 1), CellType::Wall);
	}
	for (int y = 1; y < rows - 1; ++y) {
		set(Point(0, y), CellType::Wall);
		set(Point(cols - 1, y), CellType::Wall);
	}

	//清空剩余单元格
	for (int y = 1; y < rows - 1; ++y) {
		for (int x = 1; x < cols - 1; ++x) {
			set(Point(x, y), CellType::Empty);
		}
	}
}

Map::CellType Map::get(Point<int> pos) const {
	if (pos.x < 0 || pos.x > cols - 1 || pos.y < 0 || pos.y > rows - 1) {
		return CellType::Wall;
	}

	return map_[1LL * pos.x * rows + pos.y];
}

void Map::set(Point<int> pos, CellType type) {
	if (pos.x < 0 || pos.x > cols - 1 || pos.y < 0 || pos.y > rows - 1) { return; }

	map_[1LL * pos.x * rows + pos.y] = type;
}

void Map::generate(CellType foodType) {
	if (foodType != CellType::Food && foodType != CellType::RedFood) { return; }

	//遍历取出地图上所有空位，再随机抽取一空位生成食物
	std::vector<Point<int>> emptyCells;

	for (int x = 1; x < cols - 1; ++x) {
		for (int y = 1; y < rows - 1; ++y) {
			if (get(Point(x, y)) == CellType::Empty) {
				emptyCells.emplace_back(x, y);
			}
		}
	}

	if (emptyCells.empty()) { return; }

	size_t random = utils::getRandom(emptyCells.size() - 1);
	set(emptyCells[random], foodType);
}

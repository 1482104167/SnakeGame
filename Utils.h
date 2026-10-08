//Utils.h
#pragma once

#include <random>
#include <type_traits>

namespace utils {
	//生成指定区间内随机数
	template<typename T>
	T getRandom(T minVal, T maxVal) {
		if (minVal >= maxVal) {
			return minVal;
		}

		static std::mt19937 gen(std::random_device{}());

		if constexpr (std::is_integral_v<T>) {
			std::uniform_int_distribution<T> dis(minVal, maxVal);
			return dis(gen);
		}
		else if constexpr (std::is_floating_point_v<T>) {
			std::uniform_int_distribution<T> dis(minVal, maxVal);
			return dis(gen);
		}
		else {
			return minVal;
		}
	}

	template<typename T>
	T getRandom(T maxVal) {
		return getRandom<T>(0, maxVal);
	}
}

//Point.h
#pragma once

template<typename T>
struct Point {
	T x;
	T y;

	//比较运算符
	constexpr bool operator==(const Point&) const = default;

	//复合赋值运算符：支持向量加减乘除和标量乘除，规则均为逐分量计算
	constexpr Point& operator+=(const Point& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	constexpr Point& operator-=(const Point& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	constexpr Point& operator*=(const Point& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	constexpr Point& operator/=(const Point& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	constexpr Point& operator*=(T scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	constexpr Point& operator/=(T scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	//二元算术运算符：支持向量加减乘除和标量乘除，规则均为逐分量计算
	constexpr Point operator+(const Point& other) const {
		Point result = *this;
		result += other;
		return result;
	}

	constexpr Point operator-(const Point& other) const {
		Point result = *this;
		result -= other;
		return result;
	}

	constexpr Point operator*(const Point& other) const {
		Point result = *this;
		result *= other;
		return result;
	}

	constexpr Point operator/(const Point& other) const {
		Point result = *this;
		result /= other;
		return result;
	}

	constexpr Point operator*(T scalar) const {
		Point result = *this;
		result *= scalar;
		return result;
	}

	constexpr Point operator/(T scalar) const {
		Point result = *this;
		result /= scalar;
		return result;
	}

	//支持标量左乘
	friend constexpr Point operator*(T scalar, const Point& point) {
		return point * scalar;
	}
};

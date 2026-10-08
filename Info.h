//Info.h
#pragma once

//游戏状态
enum class GameStatus : unsigned char {
	Idle, Active, Lose, Win, Pause, Quit
};

class Info {
public:
	//速度增加次数上限
	static constexpr int increaseSpeedMaxTimes = 20;

	//默认构造函数
	Info() = default;

	//禁用拷贝构造和赋值
	Info(const Info&) = delete;
	Info& operator=(const Info&) = delete;

	//默认移动构造和赋值
	Info(Info&&) noexcept = default;
	Info& operator=(Info&&) noexcept = default;

	//获取速度
	int speed() const { return speed_; }
	//获取分数
	int score() const { return score_; }
	//获取游戏状态
	GameStatus status() const { return status_; }
	//设置游戏状态
	void setStatus(GameStatus status) { status_ = status; }

	//重置数据
	void reset();
	//增加移速
	void increaseSpeed();
	//增加分数
	void increaseScore();

private:
	//初始速度，单次速度增量，最大速度（数值含义为 每秒移动格数 * 1000）
	static constexpr int initSpeed = 4125;
	static constexpr int speedIncrement = 75;
	static constexpr int maxSpeed = initSpeed + increaseSpeedMaxTimes * speedIncrement;

	//单次分数增量
	static constexpr int scoreIncrement = 5;

	int speed_ = initSpeed;
	int score_ = 0;
	GameStatus status_ = GameStatus::Idle;
};

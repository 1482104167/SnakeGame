//Settings.h
#pragma once

class Settings {
public:
	//默认构造函数
	Settings() = default;

	//禁用拷贝构造和赋值
	Settings(const Settings&) = delete;
	Settings& operator=(const Settings&) = delete;

	//默认移动构造和赋值
	Settings(Settings&&) noexcept = default;
	Settings& operator=(Settings&&) noexcept = default;

	//获取多食物设置
	bool isNoRedFood() const { return isNoRedFood_; }
	//获取无界设置
	bool isUnbounded() const { return isUnbounded_; }
	//获取暂停设置
	bool isAllowPause() const { return isAllowPause_; }
	//获取无敌设置
	bool isInvincible() const { return isInvincible_; }

	//重置数据
	void reset();
	//调节多食物设置
	void toggleIsNoRedFood();
	//调节无界设置
	void toggleIsUnbounded();
	//调节暂停设置
	void toggleIsAllowPause();
	//调节无敌设置
	void toggleIsInvincible();

private:
	bool isNoRedFood_ = false;
	bool isUnbounded_ = false;
	bool isAllowPause_ = false;
	bool isInvincible_ = false;
};

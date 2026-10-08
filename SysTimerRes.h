//SysTimerRes.h
#pragma once

class SysTimerRes {
public:
	//构造函数：设置系统计时器分辨率
	explicit SysTimerRes(unsigned period);

	//析构函数：重置计时器分辨率
	~SysTimerRes();

	//禁用拷贝构造和赋值
	SysTimerRes(const SysTimerRes&) = delete;
	SysTimerRes& operator=(const SysTimerRes&) = delete;

	//禁用移动构造和赋值
	SysTimerRes(SysTimerRes&&) = delete;
	SysTimerRes& operator=(SysTimerRes&&) = delete;

	//获取设置是否成功
	bool success() const { return success_; }

private:
	unsigned period_ = 1;
	bool success_ = false;
};
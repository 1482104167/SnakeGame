//SysTimerRes.cpp
#include "SysTimerRes.h"

#include <Windows.h>

#pragma comment(lib, "winmm.lib")

SysTimerRes::SysTimerRes(unsigned period) : period_(period) {
	if (timeBeginPeriod(period_) == TIMERR_NOERROR) {
		success_ = true;
	}
}

SysTimerRes::~SysTimerRes() {
	if (success_) {
		timeEndPeriod(period_);
		success_ = false;
	}
}

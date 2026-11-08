//Settings.cpp
#include "Settings.h"

void Settings::reset() {
	isNoRedFood_ = false;
	isUnbounded_ = false;
	isAllowPause_ = false;
	isInvincible_ = false;
}

void Settings::toggleIsNoRedFood() {
	isNoRedFood_ = !isNoRedFood_;
}

void Settings::toggleIsUnbounded() {
	isUnbounded_ = !isUnbounded_;
}

void Settings::toggleIsAllowPause() {
	isAllowPause_ = !isAllowPause_;
}

void Settings::toggleIsInvincible() {
	isInvincible_ = !isInvincible_;
}

//Settings.cpp
#include "Settings.h"

void Settings::reset() {
	*this = Settings();
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

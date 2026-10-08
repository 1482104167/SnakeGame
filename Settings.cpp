//Settings.cpp
#include "Settings.h"

void Settings::reset() {
	*this = Settings();
}

void Settings::toggleIsMoreFood() {
	isMoreFood_ = !isMoreFood_;
}

void Settings::toggleIsUnbounded() {
	isUnbounded_ = !isUnbounded_;
}

void Settings::toggleCanPause() {
	canPause_ = !canPause_;
}

void Settings::toggleIsInvincible() {
	isInvincible_ = !isInvincible_;
}

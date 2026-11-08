//Info.cpp
#include "Info.h"

import std;

void Info::reset() {
	speed_ = initSpeed;
	score_ = 0;
	status_ = GameStatus::Idle;
}

void Info::increaseSpeed() {
	speed_ = (std::min)(speed_ + speedIncrement, maxSpeed);
}

void Info::increaseScore() {
	score_ += scoreIncrement;
}

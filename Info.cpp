//Info.cpp
#include "Info.h"

import std;

void Info::reset() {
	*this = Info();
}

void Info::increaseSpeed() {
	speed_ = (std::min)(speed_ + speedIncrement, maxSpeed);
}

void Info::increaseScore() {
	score_ += scoreIncrement;
}

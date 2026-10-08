//Input.cpp
#include "Input.h"

#include <conio.h>

import std;

std::optional<int> Input::pullKey() {
	if (!_kbhit()) {
		return std::nullopt;
	}
	return _getch();
}

int Input::waitKey() {
	return _getch();
}

void Input::pushKey(int key) {
	_ungetch(key);
}

void Input::flush() {
	while (_kbhit()) {
		(void)_getch();
	}
}

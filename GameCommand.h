//GameCommand.h
#pragma once

#include <optional>

//游戏命令
enum class GameCommand : unsigned char {
	Up, Down, Left, Right, TogglePause, Quit
};

//将按键转换为游戏命令
inline std::optional<GameCommand> toGameCommand(int key) {
	switch (key) {
	case 'w': case 'W':
		return GameCommand::Up;
	case 's': case 'S':
		return GameCommand::Down;
	case 'a': case 'A':
		return GameCommand::Left;
	case 'd': case 'D':
		return GameCommand::Right;
	case ' ':
		return GameCommand::TogglePause;
	case '\x1b'://Esc
		return GameCommand::Quit;
	default:
		return std::nullopt;
	}
}

#pragma once
#include <Windows.h>

class Console {
private:
	int columns, rows;

public:
	Console();
	void SetConsoleDimensions();
	int GetConsoleLength();
	int GetConsoleHeight();
};
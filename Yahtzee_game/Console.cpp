#include "Console.h"
#include <iostream>
// maybe add methods that can also manipulate the console

Console::Console():
	columns(0), rows(0)
{
	// empty
}

void Console::SetConsoleDimensions()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	columns = col;
	rows = row;
}

int Console::GetConsoleLength()
{
	return columns;
}

int Console::GetConsoleHeight()
{
	return rows;
}





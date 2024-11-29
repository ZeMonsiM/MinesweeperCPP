//
// Created by matth on 25/11/2024.
//

#include "TermColor.h"
#include <Windows.h>

void setTerminalColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
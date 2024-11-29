//
// Created by matth on 25/11/2024.
//

#include <iostream>
#include <random>
#include "Grid.h"
#include "TermColor.h"

#include <cstring>
using namespace std;

Grid::Grid() : grid(10, vector(10, Square())) {
}

Grid::Grid(int size, int numberOfBombs) : grid(size, vector(size, Square())) {
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < numberOfBombs; i++) {
        while (true) {
            int row = gen() % size;
            int column = gen() % size;

            if (!grid[row][column].isBomb()) {
                // Place a bomb at the randomly selected square
                grid[row][column] = Square(true);

                // Increase bomb counters for surrounding non-bomb squares
                if (row > 0 && !grid[row - 1][column].isBomb()) {
                    grid[row - 1][column].incrementValue();
                }
                if (column > 0 && !grid[row][column - 1].isBomb()) {
                    grid[row][column - 1].incrementValue();
                }
                if (column < size - 1 && !grid[row][column + 1].isBomb()) {
                    grid[row][column + 1].incrementValue();
                }
                if (row < size - 1 && !grid[row + 1][column].isBomb()) {
                    grid[row + 1][column].incrementValue();
                }
                if (row > 0 && column > 0 && !grid[row - 1][column - 1].isBomb()) {
                    grid[row - 1][column - 1].incrementValue();
                }
                if (row > 0 && column < size - 1 && !grid[row - 1][column + 1].isBomb()) {
                    grid[row - 1][column + 1].incrementValue();
                }
                if (row < size - 1 && column > 0 && !grid[row + 1][column - 1].isBomb()) {
                    grid[row + 1][column - 1].incrementValue();
                }
                if (row < size - 1 && column < size - 1 && !grid[row + 1][column + 1].isBomb()) {
                    grid[row + 1][column + 1].incrementValue();
                }

                break;
            }
        }
    }
}

void Grid::display() const {
    int colors[8] = {COLOR_LIGHT_BLUE, COLOR_LIGHT_GREEN, COLOR_GREEN, COLOR_YELLOW, COLOR_PURPLE, COLOR_LIGHT_RED, COLOR_RED, COLOR_BLUE_GRAY};

    cout << "  ";
    for (int i = 0; i < grid.size(); i++) {
        cout << (unsigned char)(i+65) << " ";
    }
    cout << endl << " " << (unsigned char)201;
    for (int i = 0; i < grid.size(); i++) {
        cout << (unsigned char)205;
        if (i != grid.size() - 1) {
            cout << (unsigned char)205;
        }
    }
    cout << (unsigned char)187 << endl;

    for (int row = 0; row < grid.size(); row++) {
        cout << (unsigned char)(row+65) << (unsigned char)186;

        for (int col = 0; col < grid[row].size(); col++) {
            Square square = grid[row][col];
            if (square.getState() == "hide") {
                cout << "-";
            } else if (square.getState() == "show") {
                if (square.getValue() <= 0) {
                    cout << " ";
                } else {
                    setTerminalColor(colors[square.getValue() - 1]);
                    cout << square.getValue();
                    setTerminalColor(COLOR_WHITE);
                }
            } else if (square.getState() == "flagged") {
                cout << "X";
            }

            if (col != grid.size() - 1) {
                cout << " ";
            }
        }

        cout << (unsigned char)186 << endl;
    }

    cout << " " << (unsigned char)200;
    for (int i = 0; i < grid.size(); i++) {
        cout << (unsigned char)205;
        if (i != grid.size() - 1) {
            cout << (unsigned char)205;
        }
    }
    cout << (unsigned char)188 << endl;
}

std::vector<int> Grid::convertCoordinates(std::string row, std::string column) {
    if (row.length() > 1 || column.length() > 1) {return {};} // Invalid set of coordinates (invalid input length)
    char textRow[2], textColumn[2];
    int numberRow, numberColumn;
    strcpy(textRow, row.c_str());
    strcpy(textColumn, column.c_str());
    numberRow = (int)textRow[0] - 65;
    numberColumn = (int)textColumn[0] - 65;
    if (numberRow >= grid.size() || numberRow < 0 || numberColumn >= grid.size() || numberColumn < 0) {return {};} // Invalid set of coordinates (out of bounds)

    return {numberRow, numberColumn};
}

int Grid::flag(int row, int column) {
    return grid[row][column].toggleFlaggedState();
}

bool Grid::canDig(int row, int column) {
    return grid[row][column].getState() == "hide";
}

bool Grid::dig(int row, int column) {
    Square square = grid[row][column];
    if (square.isBomb()) {
        return true;
    }

    // Dig all connected squares in every direction until a non-zero square is found (except for flagged squares)
    recursiveDiscover(row, column);
    return false;
}

bool Grid::digRemainingSquares() {
    for (int row = 0; row < grid.size(); row++) {
        for (int column = 0; column < grid[row].size(); column++) {
            if (canDig(row, column)) {
                if (dig(row, column)) {
                    // Bomb has been hit
                    return true;
                }
            }
        }
    }

    // No bomb has been hit in the process
    return false;
}

bool Grid::checkForVictory() {
    for (int row = 0; row < grid.size(); row++) {
        for (int column = 0; column < grid[row].size(); column++) {
            Square square = grid[row][column];
            if (square.getState() == "hide" && !square.isBomb()) {
                return false;
            }
        }
    }

    return true;
}

void Grid::recursiveDiscover(int row, int column) {
    // Initial checks
    if (row < 0 || row >= grid.size() || column < 0 || column >= grid.size()) {
        return; // Out of bounds
    }

    Square& square = grid[row][column];
    if (square.getState() == "flagged" || square.getState() == "show") {
        return; // Stop if a flagged square (or if an already discovered square) has been found
    }

    // Reveal the current square
    square.reveal();

    // Check squares in the four surrounding directions if the current square does not have any bomb around it
    if (square.getValue() == 0) {
        if (row > 0) {
            recursiveDiscover(row - 1, column);
        }

        if (row < grid.size() - 1) {
            recursiveDiscover(row + 1, column);
        }

        if (column > 0) {
            recursiveDiscover(row, column - 1);
        }

        if (column < grid.size() - 1) {
            recursiveDiscover(row, column + 1);
        }
    }
}

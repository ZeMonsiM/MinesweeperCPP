//
// Created by matth on 25/11/2024.
//

#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Square.h"


class Grid {
    std::vector<std::vector<Square>> grid; // 2D Matrix of the squares
    void recursiveDiscover(int row, int column); // Recursively show connected squares until a non zero square is found or if the edge of the board has been reached

public:
    Grid(); // Default constructor : generates a grid with default size of 10 and 7 bombs
    Grid(int size, int numberOfBombs); // Constructor : generates a grid with specific size and number of bombs (max size : 25)

    void display() const; // Displays the board on the screen
    std::vector<int> convertCoordinates(std::string row, std::string column); // Converts letter coordinates into indexes. Returns an empty vector if at least one coordinate is invalid
    int flag(int row, int column); // Flag a square on the board at the coordinates row:column (mark a bomb). Return 0 if the square cannot be flagged
    bool canDig(int row, int column); // Returns true if the player can dig the square at the coordinates row:column
    bool dig(int row, int column); // Dig a square on the board at the coordinates row:column (explode if bomb, show value if not). Returns true if a bomb detonates and false otherwise
    bool digRemainingSquares(); // Endgame method to reveal the remaining squares if all flags have been placed on the board. Same logic than dig() (will return true if a bomb explodes)
    bool checkForVictory(); // Returns true if the player revealed all non-bomb squares on the board
};



#endif //GRID_H

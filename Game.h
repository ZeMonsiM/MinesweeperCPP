//
// Created by matth on 25/11/2024.
//

#ifndef GAME_H
#define GAME_H
#include "Grid.h"


class Game {
    Grid grid; // Grid object used in the game
    int numberOfBombs; // The number of bombs on the grid
    int flagsPlaced; // Number of flags placed by the player
    std::string playerName; // The game of the player

    std::string mainMenu(); // Displays the main menu, asks the player to do something and returns the action

public:
    Game(); // Constructor : initializes the game
    bool play(); // Starts the game. Returns true if the player wins and false if the player loses
    bool defeat(); // Show the defeat screen. Returns true if the player chooses to start another game
    void victory(); // Show the victory screen
};



#endif //GAME_H

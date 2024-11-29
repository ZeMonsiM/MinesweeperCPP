//
// Created by matth on 25/11/2024.
//

#include "Game.h"
#include <string>
#include <iostream>

#include "TermColor.h"

using namespace std;

std::string Game::mainMenu() {
    string input;
    cout << "[F] Flag / Unflag a square as a bomb" << endl;
    cout << "[R] Reveal a square on the board" << endl;
    cout << "[Q] Quit game" << endl << endl;
    while (true) {
        cout << ">";
        getline(cin, input);
        if (input == "F" || input == "R" || input == "Q") {
            return input;
        }
    }
}

Game::Game() : grid(Grid()), flagsPlaced(0) {
    string difficulty;
    cout << "What is your name ?" << endl << ">";
    getline(cin, playerName);

    cout << endl << "Hello " << playerName << "!" << endl << endl;

    cout << "Select a difficulty level :" << endl;
    cout << "> EASY (9x9 grid with 10 bombs)" << endl;
    cout << "> MEDIUM (16x16 grid with 40 bombs)" << endl;
    cout << "> HARD (25x25 grid with 80 bombs)" << endl;
    cout << "> EXTREME (25x25 grid with 99 bombs)" << endl << endl;

    while (true) {
        cout << "Difficulty level" << endl << ">";
        getline(cin, difficulty);

        if (difficulty == "EASY") {
            cout << endl << "Playing on easy difficulty !" << endl;
            grid = Grid(9, 10);
            numberOfBombs = 10;
            break;
        }

        if (difficulty == "MEDIUM") {
            cout << endl << "Playing on medium difficulty !" << endl;
            grid = Grid(16, 40);
            numberOfBombs = 40;
            break;
        }

        if (difficulty == "HARD") {
            cout << endl << "Playing on hard difficulty !" << endl;
            grid = Grid(25, 80);
            numberOfBombs = 80;
            break;
        }

        if (difficulty == "EXTREME") {
            cout << endl << "Playing on extreme difficulty !" << endl;
            grid = Grid(25, 99);
            numberOfBombs = 99;
            break;
        }

        cout << "Invalid difficulty level ! Please enter EASY, MEDIUM, HARD or EXTREME !" << endl;
    }
}

bool Game::play() {
    while (true) {
        if (grid.checkForVictory()) {
            return true;
        }

        grid.display();
        cout << endl << "You have placed " << flagsPlaced << "/" << numberOfBombs << " flags..." << endl << endl;

        if (flagsPlaced == numberOfBombs) {
            string input;
            cout << "All flags have been placed ! Do you want to reveal the remaining squares ?" << endl;
            while (true) {
                cout << "(y/n) >";
                getline(cin, input);
                if (input == "y" || input == "Y" || input == "n" || input == "N") {
                    break;
                }
            }

            if (input == "y" || input == "Y") {
                if (grid.digRemainingSquares()) {
                    return false; // Game over (a bomb has been hit during the digging process)
                }

                return true; // Player wins
            }
        }

        string input = mainMenu();
        if (input == "Q") {
            return false;
        }

        string row, column;
        vector<int> coordinates;
        cout << "Please enter the coordinates (or the '$' character to cancel) ..." << endl;
        while (true) {
            cout << endl << "Row >";
            getline(cin, row);
            cout << "Column >";
            getline(cin, column);
            coordinates = grid.convertCoordinates(row, column);
            if (!coordinates.empty() || row == "$" || column == "$") {
                break;
            }
        }

        if (row == "$" || column == "$") {
            continue; // Cancelled by user
        }

        if (input == "F") {
            int variation = grid.flag(coordinates[0], coordinates[1]);
            if (variation == 0) {
                cout << "Cannot flag this square !" << endl;
            } else {
                flagsPlaced += variation;
            }
        }

        if (input == "R") {
            if (grid.canDig(coordinates[0], coordinates[1])) {
                if (grid.dig(coordinates[0], coordinates[1])) {
                    return false; // Game over (a bomb has been hit by the player)
                }
            }
        }
    }
}

bool Game::defeat() {
    setTerminalColor(COLOR_RED);
    cout << endl << "You lost !" << endl;
    setTerminalColor(COLOR_WHITE);
    grid.display();

    string tryAgain;
    cout << "Try again ?" << endl;
    while (true) {
        cout << "(y/n) >";
        getline(cin, tryAgain);
        if (tryAgain == "y" || tryAgain == "Y") {
            return true;
        }
        if (tryAgain == "n" || tryAgain == "N") {
            return false;
        }
    }
}

void Game::victory() {
    setTerminalColor(COLOR_GREEN);
    cout << endl << "YOU WIN !" << endl;
    setTerminalColor(COLOR_WHITE);
    grid.display();
}

//
// Created by matth on 25/11/2024.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <optional>
#include <string>


class Square {
    std::string state; // State of the square. Can be set to "hide", "show" or "flagged"
    bool bomb; // Set to true if the square has a bomb
    std::optional<int> value; // An optional value for the number of bombs around the square

public:
    Square(); // Default constructor : creates an empty square
    Square(bool bomb); // Constructor : creates a square

    std::string getState(); // Returns square state ("hide"/"show"/"flagged")
    bool isBomb(); // Returns true if the square is a bomb
    int getValue(); // Returns the value of the square

    int incrementValue(); // Increases the value by 1
    int toggleFlaggedState(); // Toggles between the "hide" and "flagged" states and returns the variation of flags (1 if a new flag has been added and -1 if an existing flag has been removed)
    bool reveal(); // Set the square to a "show" state. Returns true for success and false for failure
};



#endif //SQUARE_H

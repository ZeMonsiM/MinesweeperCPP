//
// Created by matth on 25/11/2024.
//

#include "Square.h"
#include <iostream>

Square::Square() : state("hide"), value(0), bomb(false) {
}

Square::Square(bool bomb) : state("hide"), value(0), bomb(bomb) {
}

std::string Square::getState() {
    return state;
}

bool Square::isBomb() {
    return bomb;
}

int Square::getValue() {
    return value.value_or(-1);
}

int Square::incrementValue() {
    if (!value.has_value()) {
        return -1;
    }

    value = value.value() + 1;
    return value.value();
}

int Square::toggleFlaggedState() {
    if (state == "hide") {
        state = "flagged";
        return 1;
    }

    if (state == "flagged") {
        state = "hide";
        return -1;
    }

    return 0; // Cannot flag a square that has been revealed
}

bool Square::reveal() {
    if (state != "hide") {
        return false;
    }

    this->state = "show";
    return true;
}

#pragma once
#include <string>

enum class Unit {
    GRAMS,
    KILOGRAMS,
    MILLILITERS,
    LITERS,
    CUPS,
    TABLESPOONS,
    TEASPOONS,
    PIECES,
    NONE
};

std::string unitToString(Unit unit);

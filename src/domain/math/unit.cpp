#include "unit.hpp"

std::string unitToString(Unit unit) {
    // Implementation goes here
    switch(unit) {
        case Unit::GRAMS: return "g";
        case Unit::KILOGRAMS: return "kg";
        case Unit::MILLILITERS: return "ml";
        case Unit::LITERS: return "l";
        case Unit::CUPS: return "cups";
        case Unit::TABLESPOONS: return "tbsp";
        case Unit::TEASPOONS: return "tsp";
        case Unit::PIECES: return "pcs";
        case Unit::NONE: return "";
        default: return "";
    }
}
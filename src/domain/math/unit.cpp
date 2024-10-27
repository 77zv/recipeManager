#include "unit.hpp"

std::string unitToString(Unit unit) {
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

double convertTo(double amount, Unit from, Unit to) {
    if (from == to) return amount;
    
    // Base -> Target for a universal conversion
    double baseAmount;
    
    // (ml or g) Current -> Base
    switch (from) {
        // Volume
        case Unit::MILLILITERS: baseAmount = amount; break;
        case Unit::LITERS: baseAmount = amount * 1000; break;
        case Unit::CUPS: baseAmount = amount * 236.588; break;
        case Unit::TABLESPOONS: baseAmount = amount * 14.7868; break;
        case Unit::TEASPOONS: baseAmount = amount * 4.92892; break;
        
        // Weight
        case Unit::GRAMS: baseAmount = amount; break;
        case Unit::KILOGRAMS: baseAmount = amount * 1000; break;
        
        // Non-convertible
        case Unit::PIECES:
        case Unit::NONE:
        default:
            throw std::invalid_argument("Cannot convert between these units");
    }
    
    // (ml or g) Base -> Target
    switch (to) {
        // Volume
        case Unit::MILLILITERS: return baseAmount;
        case Unit::LITERS: return baseAmount / 1000;
        case Unit::CUPS: return baseAmount / 236.588;
        case Unit::TABLESPOONS: return baseAmount / 14.7868;
        case Unit::TEASPOONS: return baseAmount / 4.92892;
        
        // Weight
        case Unit::GRAMS: return baseAmount;
        case Unit::KILOGRAMS: return baseAmount / 1000;
        
        // Non-convertible
        case Unit::PIECES:
        case Unit::NONE:
        default:
            throw std::invalid_argument("Cannot convert between these units");
    }
}

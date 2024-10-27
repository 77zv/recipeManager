#pragma once
#include "quantity.hpp"

class Ingredient {
private:
    std::string name;
    Quantity quantity;

public:
    Ingredient(std::string name, Quantity quantity);
    std::string getName() const;
    Quantity getQuantity() const;
    void setQuantity(Quantity quantity);
};
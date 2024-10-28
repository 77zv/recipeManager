#pragma once
#include "../math/quantity.hpp"

class Ingredient {
private:
    std::string name;
    Quantity quantity;

public:
    Ingredient(const std::string&& name, Quantity quantity);
    std::string getName() const;
    Quantity getQuantity() const;
    void setQuantity(Quantity quantity);
};
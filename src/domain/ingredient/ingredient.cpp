#include "ingredient.hpp"

Ingredient::Ingredient(std::string name) : name(std::move(name)) {}

std::string Ingredient::getName() const {
    return name;
}
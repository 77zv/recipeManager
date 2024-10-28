#include "ingredient.hpp"

Ingredient::Ingredient(const std::string&& name, Quantity quantity) : name(std::move(name)), quantity(quantity) {}

std::string Ingredient::getName() const {
    return name;
}

Quantity Ingredient::getQuantity() const {
    return quantity;
}

void Ingredient::setQuantity(Quantity newQuantity) {
    quantity = newQuantity;
}
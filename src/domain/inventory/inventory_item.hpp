#pragma once
#include "../ingredient/ingredient.hpp"

class InventoryItem {
private:
    Ingredient ingredient;
    Quantity quantity;

public:
    InventoryItem(const Ingredient& ingredient, Quantity quantity);
    Ingredient getIngredient() const;
    Quantity getQuantity() const;
    void setQuantity(Quantity quantity);
    void addQuantity(Quantity quantity);
    void removeQuantity(Quantity quantity);
};
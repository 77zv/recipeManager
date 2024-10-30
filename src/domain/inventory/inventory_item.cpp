#include "inventory_item.hpp"
#include "../math/quantity.hpp"

InventoryItem::InventoryItem(const Ingredient& ingredient, Quantity quantity) : ingredient(ingredient), quantity(quantity) {}

Ingredient InventoryItem::getIngredient() const {
    return ingredient;
}

Quantity InventoryItem::getQuantity() const {
    return quantity;
}

void InventoryItem::setQuantity(Quantity quantity) {
    this->quantity = quantity;
}

void InventoryItem::addQuantity(Quantity quantity) {
    this->quantity = this->quantity + quantity;
}

void InventoryItem::removeQuantity(Quantity quantity) { 
    this->quantity = this->quantity - quantity;
}
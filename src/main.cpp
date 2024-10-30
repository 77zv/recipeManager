#include <iostream>
#include "domain/ingredient/ingredient.hpp"
#include "domain/math/quantity.hpp"
#include "domain/math/unit.hpp"
#include "domain/inventory/inventory_item.hpp"

int main(int, char**) {
    Ingredient flour("Flour");
    Ingredient sugar("Sugar");

    Quantity quantity(1, Unit::LITERS);
    Quantity quantity2(3, Unit::MILLILITERS);

    InventoryItem flourStock(flour, quantity);
    InventoryItem sugarStock(sugar, quantity2);

    std::cout << flourStock.getIngredient().getName() << " " 
              << flourStock.getQuantity().getAmount() << " " 
              << unitToString(flourStock.getQuantity().getUnit()) << "\n";

    std::cout << "Hello, from recipeManager!\n";
}
        

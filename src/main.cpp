#include <iostream>
#include "domain/ingredient/ingredient.hpp"
#include "domain/math/quantity.hpp"
#include "domain/math/unit.hpp"
#include "domain/inventory/inventory_item.hpp"

int main(int, char**){
    std::string flour = "Flour";
    std::string sugar = "Sugar";

    Quantity quantity(1, Unit::LITERS);
    Quantity quantity2(3, Unit::MILLILITERS);

    Ingredient ingredient(std::move(flour), quantity);
    Ingredient ingredient2(std::move(sugar), quantity2);

    Quantity sum = ingredient.getQuantity() + ingredient2.getQuantity();

    InventoryItem inventoryItem(ingredient, ingredient.getQuantity());

    std::cout << sum.getAmount() << " " << unitToString(sum.getUnit()) << "\n";

    std::cout << ingredient.getName() << " " << ingredient.getQuantity().getAmount() << " " << unitToString(ingredient.getQuantity().getUnit()) << "\n";

    std::cout << "Hello, from recipeManager!\n";
}
        

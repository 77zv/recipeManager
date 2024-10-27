#include <iostream>
#include "domain/ingredient/ingredient.hpp"
#include "domain/math/quantity.hpp"
#include "domain/math/unit.hpp"

int main(int, char**){

    Ingredient ingredient("Flour", Quantity(1, Unit::KILOGRAMS));

    std::cout << ingredient.getName() << " " << ingredient.getQuantity().getAmount() << " " << unitToString(ingredient.getQuantity().getUnit()) << "\n";

    std::cout << "Hello, from recipeManager!\n";
}
        

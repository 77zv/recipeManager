#include <iostream>
#include "domain/ingredient/ingredient.hpp"
#include "domain/math/quantity.hpp"
#include "domain/math/unit.hpp"
#include "domain/inventory/inventory_item.hpp"
#include "infrastructure/database/database_connection.hpp"
// #include "repository/sqlite/sqlite_ingredient_repository.hpp"

int main(int, char**) {
    try {
        DatabaseConnection& db = DatabaseConnection::getInstance(); // fuckery 
        std::cout << "Database connection successful!\n";

        // SQLiteIngredientRepository ingredientRepo;

        Ingredient flour("Flour");
        Ingredient sugar("Sugar");
        
        // ingredientRepo.save(flour);
        // ingredientRepo.save(sugar);
        std::cout << "Ingredients saved successfully!\n";

        // auto foundFlour = ingredientRepo.findByName("Flour");
        // if (foundFlour) {
        //     std::cout << "Found ingredient: " << foundFlour->getName() << "\n";
        // } else {
        //     std::cout << "Ingredient not found!\n";
        // }

        // std::cout << "Database tests completed successfully!\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
        

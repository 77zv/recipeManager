#include <iostream>
#include <memory>
#include "infrastructure/database/database_connection.hpp"
#include "repository/sqlite/sqlite_ingredient_repository.hpp"
#include "repository/sqlite/sqlite_inventory_item_repository.hpp"
#include "repository/sqlite/sqlite_recipe_repository.hpp"

void testIngredientRepository(std::shared_ptr<SQLiteIngredientRepository> repo) {
    std::cout << "\n=== Testing Ingredient Repository ===\n";
    
    // Create
    Ingredient flour("Flour");
    repo->save(flour);
    std::cout << "Created ingredient: " << flour.getName() << "\n";
    
    // Read
    auto retrieved = repo->findByName("Flour");
    if (retrieved) {
        std::cout << "Retrieved: " << retrieved->getName() << "\n";
    }
    
    // List all
    auto all = repo->findAll();
    std::cout << "Total ingredients: " << all.size() << "\n";
    
    // Delete
    repo->remove("Flour");
    std::cout << "Deleted ingredient\n";
}

void testInventoryItemRepository(std::shared_ptr<SQLiteInventoryItemRepository> repo) {
    std::cout << "\n=== Testing Inventory Item Repository ===\n";
    
    // Create
    Ingredient flour("Flour");
    Quantity quantity(500, Unit::GRAMS);
    InventoryItem item(flour, quantity);
    repo->save(item);
    std::cout << "Created inventory item\n";
    
    // Read
    auto retrieved = repo->findByName("Flour");
    if (retrieved) {
        std::cout << "Retrieved: " << retrieved->getIngredient().getName() 
                 << " - " << retrieved->getQuantity().getAmount() << "\n";
    }
    
    // Update
    item.setQuantity(Quantity(750, Unit::GRAMS));
    repo->update(item);
    std::cout << "Updated quantity\n";
    
    // Delete
    repo->remove("Flour");
    std::cout << "Deleted inventory item\n";
}

void testRecipeRepository(std::shared_ptr<SQLiteRecipeRepository> repo) {
    std::cout << "\n=== Testing Recipe Repository ===\n";
    
    // Create a recipe with steps
    std::vector<RecipeStep> steps;
    std::vector<Ingredient> ingredients = {Ingredient("Flour")};
    steps.emplace_back(1, "Mix flour", Quantity(500, Unit::GRAMS), ingredients);
    
    Recipe recipe("Basic Bread", steps);
    repo->save(recipe);
    std::cout << "Created recipe\n";
    
    // Read
    auto retrieved = repo->findByName("Basic Bread");
    if (retrieved) {
        std::cout << "Retrieved: " << retrieved->getName() 
                 << " with " << retrieved->getSteps().size() << " steps\n";
    }
    
    // Delete
    repo->remove("Basic Bread");
    std::cout << "Deleted recipe\n";
}

int main() {
    try {
        auto& dbConnection = DatabaseConnection::getInstance();
        
        auto ingredientRepo = std::make_shared<SQLiteIngredientRepository>();
        auto inventoryRepo = std::make_shared<SQLiteInventoryItemRepository>();
        auto recipeRepo = std::make_shared<SQLiteRecipeRepository>();
        
        testIngredientRepository(ingredientRepo);
        testInventoryItemRepository(inventoryRepo);
        testRecipeRepository(recipeRepo);
        
        std::cout << "\nAll tests completed successfully!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
        

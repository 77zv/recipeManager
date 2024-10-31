#include "sqlite_ingredient_repository.hpp"
#include <SQLiteCpp/SQLiteCpp.h>

SQLiteIngredientRepository::SQLiteIngredientRepository() 
    : dbConn(DatabaseConnection::getInstance()) {}

void SQLiteIngredientRepository::save(const Ingredient& ingredient) {
    try {
        SQLite::Statement query(dbConn.getDatabase(), 
            "INSERT INTO ingredients (name) VALUES (?)");
        
        query.bind(1, ingredient.getName());
        query.exec();
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to save ingredient: " + std::string(e.what()));
    }
}

std::optional<Ingredient> SQLiteIngredientRepository::findByName(const std::string& name) {
    try {
        SQLite::Statement query(dbConn.getDatabase(), 
            "SELECT name FROM ingredients WHERE name = ?");
        query.bind(1, name);

        if (query.executeStep()) {
            std::string ingredientName = query.getColumn(0).getText();
            return Ingredient(ingredientName);
        }
        return std::nullopt;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to find ingredient: " + std::string(e.what()));
    }
}

std::vector<Ingredient> SQLiteIngredientRepository::findAll() {
    try {
        SQLite::Statement query(dbConn.getDatabase(), 
            "SELECT name FROM ingredients");
        
        std::vector<Ingredient> ingredients;
        while (query.executeStep()) {
            std::string name = query.getColumn(0).getText();
            ingredients.emplace_back(name);
        }
        return ingredients;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to fetch ingredients: " + std::string(e.what()));
    }
}

void SQLiteIngredientRepository::update(const Ingredient& ingredient) {
    try {
        SQLite::Statement query(dbConn.getDatabase(), 
            "UPDATE ingredients SET name = ? WHERE name = ?");
        
        query.bind(1, ingredient.getName());
        query.bind(2, ingredient.getName());  // Since name is our primary key
        query.exec();

        if (query.getChanges() == 0) {
            throw std::runtime_error("No ingredient found to update");
        }
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to update ingredient: " + std::string(e.what()));
    }
}

void SQLiteIngredientRepository::remove(const std::string& name) {
    try {
        // First check if the ingredient is referenced in any recipes or inventory
        SQLite::Statement checkQuery(dbConn.getDatabase(),
            "SELECT COUNT(*) FROM step_ingredients WHERE ingredient_name = ? "
            "UNION ALL "
            "SELECT COUNT(*) FROM inventory_items WHERE name = ?");
        
        checkQuery.bind(1, name);
        checkQuery.bind(2, name);

        if (checkQuery.executeStep()) {
            int count = checkQuery.getColumn(0).getInt();
            if (count > 0) {
                throw std::runtime_error("Cannot delete ingredient that is in use");
            }
        }

        // If no references exist, proceed with deletion
        SQLite::Statement deleteQuery(dbConn.getDatabase(),
            "DELETE FROM ingredients WHERE name = ?");
        
        deleteQuery.bind(1, name);
        deleteQuery.exec();

        if (deleteQuery.getChanges() == 0) {
            throw std::runtime_error("No ingredient found to delete");
        }
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to remove ingredient: " + std::string(e.what()));
    }
} 
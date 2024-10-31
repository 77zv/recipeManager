#include "sqlite_recipe_repository.hpp"
#include <SQLiteCpp/SQLiteCpp.h>

SQLiteRecipeRepository::SQLiteRecipeRepository()
    : dbConn(DatabaseConnection::getInstance()) {}

void SQLiteRecipeRepository::save(const Recipe& recipe) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        SQLite::Statement recipeQuery(dbConn.getDatabase(),
            "INSERT INTO recipes (name) VALUES (?)");
        recipeQuery.bind(1, recipe.getName());
        recipeQuery.exec();

        SQLite::Statement stepQuery(dbConn.getDatabase(),
            "INSERT INTO recipe_steps (recipe_name, step_number, instruction) VALUES (?, ?, ?)");
        
        SQLite::Statement ingredientQuery(dbConn.getDatabase(),
            "INSERT INTO step_ingredients (recipe_name, step_number, ingredient_name, amount, unit) "
            "VALUES (?, ?, ?, ?, ?)");

        for (const auto& step : recipe.getSteps()) {
            stepQuery.bind(1, recipe.getName());
            stepQuery.bind(2, step.getStepNumber());
            stepQuery.bind(3, step.getInstruction());
            stepQuery.exec();
            stepQuery.reset();

            for (const auto& ingredient : step.getIngredients()) {
                if (step.getQuantity()) {
                    ingredientQuery.bind(1, recipe.getName());
                    ingredientQuery.bind(2, step.getStepNumber());
                    ingredientQuery.bind(3, ingredient.getName());
                    ingredientQuery.bind(4, step.getQuantity()->getAmount());
                    ingredientQuery.bind(5, static_cast<int>(step.getQuantity()->getUnit()));
                    ingredientQuery.exec();
                    ingredientQuery.reset();
                }
            }
        }

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to save recipe: " + std::string(e.what()));
    }
}

std::optional<Recipe> SQLiteRecipeRepository::findByName(const std::string& name) {
    try {
        SQLite::Statement recipeQuery(dbConn.getDatabase(),
            "SELECT name FROM recipes WHERE name = ?");
        recipeQuery.bind(1, name);

        if (!recipeQuery.executeStep()) {
            return std::nullopt;
        }

        SQLite::Statement stepsQuery(dbConn.getDatabase(),
            "SELECT step_number, instruction FROM recipe_steps "
            "WHERE recipe_name = ? ORDER BY step_number");
        stepsQuery.bind(1, name);

        std::vector<RecipeStep> steps;
        while (stepsQuery.executeStep()) {
            int stepNumber = stepsQuery.getColumn(0).getInt();
            std::string instruction = stepsQuery.getColumn(1).getText();

            SQLite::Statement ingredientsQuery(dbConn.getDatabase(),
                "SELECT ingredient_name, amount, unit FROM step_ingredients "
                "WHERE recipe_name = ? AND step_number = ?");
            ingredientsQuery.bind(1, name);
            ingredientsQuery.bind(2, stepNumber);

            std::vector<Ingredient> ingredients;
            std::optional<Quantity> quantity;

            if (ingredientsQuery.executeStep()) {
                std::string ingredientName = ingredientsQuery.getColumn(0).getText();
                double amount = ingredientsQuery.getColumn(1).getDouble();
                Unit unit = static_cast<Unit>(ingredientsQuery.getColumn(2).getInt());

                ingredients.emplace_back(ingredientName);
                quantity = Quantity(amount, unit);
            }

            steps.emplace_back(stepNumber, instruction, quantity, ingredients);
        }

        return Recipe(std::string(name), steps);
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to find recipe: " + std::string(e.what()));
    }
}

std::vector<Recipe> SQLiteRecipeRepository::findAll() {
    try {
        SQLite::Statement recipesQuery(dbConn.getDatabase(),
            "SELECT name FROM recipes");

        std::vector<Recipe> recipes;
        while (recipesQuery.executeStep()) {
            std::string name = recipesQuery.getColumn(0).getText();
            auto recipe = findByName(name);
            if (recipe) {
                recipes.push_back(*recipe);
            }
        }
        return recipes;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to fetch recipes: " + std::string(e.what()));
    }
}

void SQLiteRecipeRepository::update(const Recipe& recipe) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        remove(recipe.getName());

        save(recipe);

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to update recipe: " + std::string(e.what()));
    }
}

void SQLiteRecipeRepository::remove(const std::string& name) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        SQLite::Statement deleteIngredients(dbConn.getDatabase(),
            "DELETE FROM step_ingredients WHERE recipe_name = ?");
        deleteIngredients.bind(1, name);
        deleteIngredients.exec();

        SQLite::Statement deleteSteps(dbConn.getDatabase(),
            "DELETE FROM recipe_steps WHERE recipe_name = ?");
        deleteSteps.bind(1, name);
        deleteSteps.exec();

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to remove recipe: " + std::string(e.what()));
    }
} 
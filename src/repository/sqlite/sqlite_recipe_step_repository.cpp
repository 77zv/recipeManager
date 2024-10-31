#include "sqlite_recipe_step_repository.hpp"
#include <SQLiteCpp/SQLiteCpp.h>

SQLiteRecipeStepRepository::SQLiteRecipeStepRepository()
    : dbConn(DatabaseConnection::getInstance()) {}

void SQLiteRecipeStepRepository::save(const std::string& recipeName, const RecipeStep& step) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        SQLite::Statement stepQuery(dbConn.getDatabase(),
            "INSERT INTO recipe_steps (recipe_name, step_number, instruction) VALUES (?, ?, ?)");
        
        stepQuery.bind(1, recipeName);
        stepQuery.bind(2, step.getStepNumber());
        stepQuery.bind(3, step.getInstruction());
        stepQuery.exec();

        SQLite::Statement ingredientQuery(dbConn.getDatabase(),
            "INSERT INTO step_ingredients (recipe_name, step_number, ingredient_name, amount, unit) "
            "VALUES (?, ?, ?, ?, ?)");

        for (const auto& ingredient : step.getIngredients()) {
            if (step.getQuantity()) {
                ingredientQuery.bind(1, recipeName);
                ingredientQuery.bind(2, step.getStepNumber());
                ingredientQuery.bind(3, ingredient.getName());
                ingredientQuery.bind(4, step.getQuantity()->getAmount());
                ingredientQuery.bind(5, static_cast<int>(step.getQuantity()->getUnit()));
                ingredientQuery.exec();
                ingredientQuery.reset();
            }
        }

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to save recipe step: " + std::string(e.what()));
    }
}

std::optional<RecipeStep> SQLiteRecipeStepRepository::findByRecipeAndStepNumber(
    const std::string& recipeName, int stepNumber) {
    try {
        SQLite::Statement stepQuery(dbConn.getDatabase(),
            "SELECT instruction FROM recipe_steps "
            "WHERE recipe_name = ? AND step_number = ?");
        
        stepQuery.bind(1, recipeName);
        stepQuery.bind(2, stepNumber);

        if (stepQuery.executeStep()) {
            std::string instruction = stepQuery.getColumn(0).getText();

            SQLite::Statement ingredientQuery(dbConn.getDatabase(),
                "SELECT i.name, si.amount, si.unit FROM step_ingredients si "
                "JOIN ingredients i ON i.name = si.ingredient_name "
                "WHERE si.recipe_name = ? AND si.step_number = ?");
            
            ingredientQuery.bind(1, recipeName);
            ingredientQuery.bind(2, stepNumber);

            std::vector<Ingredient> ingredients;
            std::optional<Quantity> quantity;

            if (ingredientQuery.executeStep()) {
                std::string ingredientName = ingredientQuery.getColumn(0).getText();
                double amount = ingredientQuery.getColumn(1).getDouble();
                Unit unit = static_cast<Unit>(ingredientQuery.getColumn(2).getInt());

                ingredients.emplace_back(ingredientName);
                quantity = Quantity(amount, unit);
            }

            return RecipeStep(stepNumber, instruction, quantity, ingredients);
        }
        return std::nullopt;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to find recipe step: " + std::string(e.what()));
    }
}

std::vector<RecipeStep> SQLiteRecipeStepRepository::findAllByRecipe(const std::string& recipeName) {
    try {
        SQLite::Statement stepQuery(dbConn.getDatabase(),
            "SELECT step_number, instruction FROM recipe_steps "
            "WHERE recipe_name = ? ORDER BY step_number");
        
        stepQuery.bind(1, recipeName);
        
        std::vector<RecipeStep> steps;
        while (stepQuery.executeStep()) {
            int stepNumber = stepQuery.getColumn(0).getInt();
            std::string instruction = stepQuery.getColumn(1).getText();

            auto step = findByRecipeAndStepNumber(recipeName, stepNumber);
            if (step) {
                steps.push_back(*step);
            }
        }
        return steps;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to fetch recipe steps: " + std::string(e.what()));
    }
}

void SQLiteRecipeStepRepository::update(const std::string& recipeName, const RecipeStep& step) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        remove(recipeName, step.getStepNumber());

        save(recipeName, step);

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to update recipe step: " + std::string(e.what()));
    }
}

void SQLiteRecipeStepRepository::remove(const std::string& recipeName, int stepNumber) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        SQLite::Statement deleteIngredients(dbConn.getDatabase(),
            "DELETE FROM step_ingredients WHERE recipe_name = ? AND step_number = ?");
        deleteIngredients.bind(1, recipeName);
        deleteIngredients.bind(2, stepNumber);
        deleteIngredients.exec();

        SQLite::Statement deleteStep(dbConn.getDatabase(),
            "DELETE FROM recipe_steps WHERE recipe_name = ? AND step_number = ?");
        deleteStep.bind(1, recipeName);
        deleteStep.bind(2, stepNumber);
        deleteStep.exec();

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to remove recipe step: " + std::string(e.what()));
    }
}

void SQLiteRecipeStepRepository::removeAllFromRecipe(const std::string& recipeName) {
    try {
        dbConn.getDatabase().exec("BEGIN TRANSACTION");

        SQLite::Statement deleteIngredients(dbConn.getDatabase(),
            "DELETE FROM step_ingredients WHERE recipe_name = ?");
        deleteIngredients.bind(1, recipeName);
        deleteIngredients.exec();

        SQLite::Statement deleteSteps(dbConn.getDatabase(),
            "DELETE FROM recipe_steps WHERE recipe_name = ?");
        deleteSteps.bind(1, recipeName);
        deleteSteps.exec();

        dbConn.getDatabase().exec("COMMIT");
    } catch (SQLite::Exception& e) {
        dbConn.getDatabase().exec("ROLLBACK");
        throw std::runtime_error("Failed to remove recipe steps: " + std::string(e.what()));
    }
} 
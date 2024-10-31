#pragma once
#include "repository/interfaces/irecipe_step_repository.hpp"
#include "infrastructure/database/database_connection.hpp"

class SQLiteRecipeStepRepository : public IRecipeStepRepository {
private:
    DatabaseConnection& dbConn;

public:
    SQLiteRecipeStepRepository();
    
    void save(const std::string& recipeName, const RecipeStep& step) override;
    std::optional<RecipeStep> findByRecipeAndStepNumber(const std::string& recipeName, int stepNumber) override;
    std::vector<RecipeStep> findAllByRecipe(const std::string& recipeName) override;
    void update(const std::string& recipeName, const RecipeStep& step) override;
    void remove(const std::string& recipeName, int stepNumber) override;
    void removeAllFromRecipe(const std::string& recipeName) override;
}; 
#pragma once
#include "../../domain/recipe/recipe_step.hpp"
#include <vector>
#include <optional>
#include <string>

class IRecipeStepRepository {
public:
    virtual ~IRecipeStepRepository() = default;
    virtual void save(const std::string& recipeName, const RecipeStep& step) = 0;
    virtual std::optional<RecipeStep> findByRecipeAndStepNumber(const std::string& recipeName, int stepNumber) = 0;
    virtual std::vector<RecipeStep> findAllByRecipe(const std::string& recipeName) = 0;
    virtual void update(const std::string& recipeName, const RecipeStep& step) = 0;
    virtual void remove(const std::string& recipeName, int stepNumber) = 0;
    virtual void removeAllFromRecipe(const std::string& recipeName) = 0;
}; 
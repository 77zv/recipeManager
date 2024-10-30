#pragma once
#include <string>
#include <vector>
#include "recipe_step.hpp"

class Recipe {
    private: 
        std::string name;
        std::vector<RecipeStep> steps;

    public:
        Recipe(const std::string&& name, const std::vector<RecipeStep>& steps);
        std::string getName() const;
        std::vector<RecipeStep> getSteps() const;
};
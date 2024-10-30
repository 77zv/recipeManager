#include "recipe.hpp"

Recipe::Recipe(const std::string&& name, const std::vector<RecipeStep>& steps) : name(std::move(name)), steps(steps) {}

std::string Recipe::getName() const {
    return name;
}

std::vector<RecipeStep> Recipe::getSteps() const {
    return steps;
}
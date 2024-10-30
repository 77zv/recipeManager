#include "recipe_step.hpp"

RecipeStep::RecipeStep(int stepNumber, const std::string& instruction, std::optional<Quantity> quantity, const std::vector<Ingredient>& ingredients) : stepNumber(stepNumber), instruction(instruction), quantity(quantity), ingredients(ingredients) {}

int RecipeStep::getStepNumber() const {
    return stepNumber;
}

std::string RecipeStep::getInstruction() const {
    return instruction;
}

std::optional<Quantity> RecipeStep::getQuantity() const {
    return quantity;
}

std::vector<Ingredient> RecipeStep::getIngredients() const {
    return ingredients;
}

void RecipeStep::setStepNumber(int newStepNumber) {
    stepNumber = newStepNumber;
}

void RecipeStep::setInstruction(const std::string& newInstruction) {
    instruction = newInstruction;
}   

void RecipeStep::setQuantity(std::optional<Quantity> newQuantity) {
    quantity = newQuantity;
}

void RecipeStep::setIngredients(const std::vector<Ingredient>& newIngredients) {
    ingredients = newIngredients;
}


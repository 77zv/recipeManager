#pragma once
#include "../ingredient/ingredient.hpp"
#include "../math/quantity.hpp"
#include <optional>
#include <vector>

class RecipeStep 
{
    private:
        int stepNumber;
        std::string instruction;
        std::optional<Quantity> quantity;
        std::vector<Ingredient> ingredients;

    public: 
        RecipeStep(int stepNumber, const std::string& instruction, std::optional<Quantity> quantity, const std::vector<Ingredient>& ingredients);

        int getStepNumber() const;
        std::string getInstruction() const;
        std::optional<Quantity> getQuantity() const;
        std::vector<Ingredient> getIngredients() const;

        void setStepNumber(int newStepNumber);
        void setInstruction(const std::string& newInstruction);
        void setQuantity(std::optional<Quantity> newQuantity);
        void setIngredients(const std::vector<Ingredient>& newIngredients);
};
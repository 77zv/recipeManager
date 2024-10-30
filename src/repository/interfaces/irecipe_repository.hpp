#pragma once
#include "domain/recipe/recipe.hpp"
#include <vector>
#include <optional>

class IRecipeRepository {
public:
    virtual ~IRecipeRepository() = default;
    virtual void save(const Recipe& recipe) = 0;
    virtual std::optional<Recipe> findByName(const std::string& name) = 0;
    virtual std::vector<Recipe> findAll() = 0;
    virtual void update(const Recipe& recipe) = 0;
    virtual void remove(const std::string& name) = 0;
}; 
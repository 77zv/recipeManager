#pragma once
#include "domain/ingredient/ingredient.hpp"
#include <vector>
#include <optional>

class IIngredientRepository {
public:
    virtual ~IIngredientRepository() = default;
    virtual void save(const Ingredient& ingredient) = 0;
    virtual std::optional<Ingredient> findByName(const std::string& name) = 0;
    virtual std::vector<Ingredient> findAll() = 0;
    virtual void update(const Ingredient& ingredient) = 0;
    virtual void remove(const std::string& name) = 0;
}; 
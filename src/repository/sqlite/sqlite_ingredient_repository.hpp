#pragma once
#include "repository/interfaces/iingredient_repository.hpp"
#include "infrastructure/database/database_connection.hpp"

class SQLiteIngredientRepository : public IIngredientRepository {
private:
    DatabaseConnection& dbConn;

public:
    SQLiteIngredientRepository();
    
    void save(const Ingredient& ingredient) override;
    std::optional<Ingredient> findByName(const std::string& name) override;
    std::vector<Ingredient> findAll() override;
    void update(const Ingredient& ingredient) override;
    void remove(const std::string& name) override;
}; 
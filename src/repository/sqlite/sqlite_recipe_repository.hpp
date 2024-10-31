#pragma once
#include "repository/interfaces/irecipe_repository.hpp"
#include "infrastructure/database/database_connection.hpp"

class SQLiteRecipeRepository : public IRecipeRepository {
private:
    DatabaseConnection& dbConn;

public:
    SQLiteRecipeRepository();
    
    void save(const Recipe& recipe) override;
    std::optional<Recipe> findByName(const std::string& name) override;
    std::vector<Recipe> findAll() override;
    void update(const Recipe& recipe) override;
    void remove(const std::string& name) override;
}; 
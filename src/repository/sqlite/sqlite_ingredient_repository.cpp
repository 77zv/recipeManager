#include "repository/interfaces/iingredient_repository.hpp"
#include "infrastructure/database/database_connection.hpp"

class SQLiteIngredientRepository : public IIngredientRepository {
private:
    DatabaseConnection& dbConn;

public:
    SQLiteIngredientRepository() 
        : dbConn(DatabaseConnection::getInstance()) {}

    void save(const Ingredient& ingredient) override {
        try {
            SQLite::Statement query(dbConn.getDatabase(), 
                "INSERT INTO ingredients (name) VALUES (?)");
            
            query.bind(1, ingredient.getName());
            query.exec();
        } catch (SQLite::Exception& e) {
            throw std::runtime_error("Failed to save ingredient: " + std::string(e.what()));
        }
    }

    std::optional<Ingredient> findByName(const std::string& name) override {
        try {
            SQLite::Statement query(dbConn.getDatabase(), 
                "SELECT name FROM ingredients WHERE name = ?");
            query.bind(1, name);

            if (query.executeStep()) {
                std::string name = query.getColumn(0).getText();
                return Ingredient(std::move(name));
            }
            return std::nullopt;
        } catch (SQLite::Exception& e) {
            throw std::runtime_error("Failed to find ingredient: " + std::string(e.what()));
        }
    }

}; 
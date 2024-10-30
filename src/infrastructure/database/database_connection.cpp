#include "database_connection.hpp"

DatabaseConnection *DatabaseConnection::instance = nullptr;

DatabaseConnection::DatabaseConnection(const std::string &dbPath)
    : db(std::make_unique<SQLite::Database>(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE))
{

    // I know names and ints as primary keys is not secure for shit, but it's a small project so just fuckin deal with it
    db->exec(R"(
        CREATE TABLE IF NOT EXISTS inventory_items (
            name TEXT PRIMARY KEY,
            amount REAL NOT NULL,
            unit INTEGER NOT NULL CHECK (unit BETWEEN 0 AND 8),
            FOREIGN KEY (name) REFERENCES ingredients(name)
        );

        CREATE TABLE IF NOT EXISTS ingredients (
            name TEXT PRIMARY KEY
        );

        CREATE TABLE IF NOT EXISTS recipes (
            name TEXT PRIMARY KEY UNIQUE,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS recipe_steps (
            recipe_name TEXT NOT NULL,
            step_number INTEGER NOT NULL,
            instruction TEXT NOT NULL,
            PRIMARY KEY (recipe_name, step_number),
            FOREIGN KEY (recipe_name) REFERENCES recipes(name)
        );
        
        CREATE TABLE IF NOT EXISTS step_ingredients (
            recipe_name TEXT NOT NULL,
            step_number INTEGER NOT NULL,
            ingredient_name TEXT NOT NULL,
            amount REAL NOT NULL,
            unit INTEGER NOT NULL CHECK (unit BETWEEN 0 AND 8),
            PRIMARY KEY (recipe_name, step_number, ingredient_name),
            FOREIGN KEY (recipe_name, step_number) REFERENCES recipe_steps(recipe_name, step_number),
            FOREIGN KEY (ingredient_name) REFERENCES ingredients(name)
        );
    )");
}

DatabaseConnection &DatabaseConnection::getInstance()
{
    if (!instance)
    {
        instance = new DatabaseConnection("recipe_manager.db");
    }
    return *instance;
}

SQLite::Database &DatabaseConnection::getDatabase()
{
    return *db;
}
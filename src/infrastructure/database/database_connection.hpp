#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>

class DatabaseConnection {
private:
    std::unique_ptr<SQLite::Database> db;
    static DatabaseConnection* instance;
    
    DatabaseConnection(const std::string& dbPath);

public:
    static DatabaseConnection& getInstance();
    SQLite::Database& getDatabase();
    
    //! DON'T FUCKING REMOVE THIS
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
}; 
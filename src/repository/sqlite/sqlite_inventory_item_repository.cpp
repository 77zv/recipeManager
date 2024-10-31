#include "sqlite_inventory_item_repository.hpp"
#include <SQLiteCpp/SQLiteCpp.h>

SQLiteInventoryItemRepository::SQLiteInventoryItemRepository()
    : dbConn(DatabaseConnection::getInstance()) {}

void SQLiteInventoryItemRepository::save(const InventoryItem& inventoryItem) {
    try {
        SQLite::Statement query(dbConn.getDatabase(),
            "INSERT INTO inventory_items (name, amount, unit) VALUES (?, ?, ?)");
        
        query.bind(1, inventoryItem.getIngredient().getName());
        query.bind(2, inventoryItem.getQuantity().getAmount());
        query.bind(3, static_cast<int>(inventoryItem.getQuantity().getUnit()));
        
        query.exec();
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to save inventory item: " + std::string(e.what()));
    }
}

std::optional<InventoryItem> SQLiteInventoryItemRepository::findByName(const std::string& name) {
    try {
        SQLite::Statement query(dbConn.getDatabase(),
            "SELECT i.name, ii.amount, ii.unit FROM inventory_items ii "
            "JOIN ingredients i ON i.name = ii.name "
            "WHERE ii.name = ?");
        
        query.bind(1, name);

        if (query.executeStep()) {
            std::string ingredientName = query.getColumn(0).getText();
            double amount = query.getColumn(1).getDouble();
            Unit unit = static_cast<Unit>(query.getColumn(2).getInt());

            Ingredient ingredient(ingredientName);
            Quantity quantity(amount, unit);
            return InventoryItem(ingredient, quantity);
        }
        return std::nullopt;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to find inventory item: " + std::string(e.what()));
    }
}

std::vector<InventoryItem> SQLiteInventoryItemRepository::findAll() {
    try {
        SQLite::Statement query(dbConn.getDatabase(),
            "SELECT i.name, ii.amount, ii.unit FROM inventory_items ii "
            "JOIN ingredients i ON i.name = ii.name");
        
        std::vector<InventoryItem> items;
        while (query.executeStep()) {
            std::string name = query.getColumn(0).getText();
            double amount = query.getColumn(1).getDouble();
            Unit unit = static_cast<Unit>(query.getColumn(2).getInt());

            Ingredient ingredient(name);
            Quantity quantity(amount, unit);
            items.emplace_back(ingredient, quantity);
        }
        return items;
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to fetch inventory items: " + std::string(e.what()));
    }
}

void SQLiteInventoryItemRepository::update(const InventoryItem& inventoryItem) {
    try {
        SQLite::Statement query(dbConn.getDatabase(),
            "UPDATE inventory_items SET amount = ?, unit = ? WHERE name = ?");
        
        query.bind(1, inventoryItem.getQuantity().getAmount());
        query.bind(2, static_cast<int>(inventoryItem.getQuantity().getUnit()));
        query.bind(3, inventoryItem.getIngredient().getName());
        
        query.exec();
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to update inventory item: " + std::string(e.what()));
    }
}

void SQLiteInventoryItemRepository::remove(const std::string& name) {
    try {
        SQLite::Statement query(dbConn.getDatabase(),
            "DELETE FROM inventory_items WHERE name = ?");
        
        query.bind(1, name);
        query.exec();
    } catch (SQLite::Exception& e) {
        throw std::runtime_error("Failed to remove inventory item: " + std::string(e.what()));
    }
} 
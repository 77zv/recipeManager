#pragma once
#include "repository/interfaces/iinventory_item_repository.hpp"
#include "infrastructure/database/database_connection.hpp"

class SQLiteInventoryItemRepository : public IInventoryItemRepository {
private:
    DatabaseConnection& dbConn;

public:
    SQLiteInventoryItemRepository();
    
    void save(const InventoryItem& inventoryItem) override;
    std::optional<InventoryItem> findByName(const std::string& name) override;
    std::vector<InventoryItem> findAll() override;
    void update(const InventoryItem& inventoryItem) override;
    void remove(const std::string& name) override;
}; 
#pragma once
#include <optional>
#include <vector>

#include "../../domain/inventory/inventory_item.hpp"

class IInventoryItemRepository {
public:
    virtual ~IInventoryItemRepository() = default;
    virtual void save(const InventoryItem& inventoryItem) = 0;
    virtual std::optional<InventoryItem> findByName(const std::string& name) = 0;
    virtual std::vector<InventoryItem> findAll() = 0;
    virtual void update(const InventoryItem& inventoryItem) = 0;
    virtual void remove(const std::string& name) = 0;
};
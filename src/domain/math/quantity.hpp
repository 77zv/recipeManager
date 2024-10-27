#pragma once
#include "../math/unit.hpp"

class Quantity {
private:
    double amount;
    Unit unit;

public:
    Quantity(double amount, Unit unit);
    
    double getAmount() const;
    Unit getUnit() const;
    void setAmount(double newAmount);
};
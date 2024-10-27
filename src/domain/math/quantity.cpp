#include "quantity.hpp"
#include <stdexcept>

Quantity::Quantity(double amount, Unit unit) : amount(amount), unit(unit) {
    if (amount < 0) {
        throw std::invalid_argument("Amount cannot be negative");
    }
}

double Quantity::getAmount() const { 
    return amount; 
}

Unit Quantity::getUnit() const { 
    return unit; 
}

void Quantity::setAmount(double newAmount) {
    if (newAmount < 0) {
        throw std::invalid_argument("Amount cannot be negative");
    }
    amount = newAmount;
}

Quantity Quantity::operator+(const Quantity& other) const {
    if (this->unit != other.unit) {
        // Convert other to this unit
        double convertedAmount = convertTo(other.amount, other.unit, this->unit);
        return Quantity(this->amount + convertedAmount, this->unit);
    }
    return Quantity(this->amount + other.amount, this->unit);
}

Quantity Quantity::operator-(const Quantity& other) const {
    if (this->unit != other.unit) {
        // Convert other to this unit
        double convertedAmount = convertTo(other.amount, other.unit, this->unit);
        return Quantity(this->amount - convertedAmount, this->unit);
    }
    return Quantity(this->amount - other.amount, this->unit);
}

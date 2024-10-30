#pragma once
#include <string>

class Ingredient {
private:
    std::string name;

public:
    explicit Ingredient(std::string name);
    std::string getName() const;
};
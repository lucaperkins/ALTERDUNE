#pragma once
#include <string>

enum class Category {
    Boss,
    MiniBoss,
    NormalMonster,
    Inconnu
};

std::string CategoryToString(Category type);
Category stringToCategory(const std::string& str);
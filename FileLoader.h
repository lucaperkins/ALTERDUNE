#pragma once
#include <vector>
#include <string>
#include "Item.h"
#include "Monster.h"
#include "ActAction.h"

class FileLoader {
public:
    static std::vector<Item>       loadItems(const std::string& path);
    static std::vector<Monster*>   loadMonstres(const std::string& path);
    static std::vector<ActAction>  loadActs(const std::string& path);

private:
    static std::string trim(const std::string& s);
    static std::string toUpper(const std::string& s);
};
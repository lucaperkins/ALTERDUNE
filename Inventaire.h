#pragma once
#include <vector>
#include "Item.h"

class Inventaire {
private:
    std::vector<Item> items;

public:
    void addItem(const Item& item);
    const Item* useItem(int i);
    void showItems() const;
    bool isEmpty() const;
};
#pragma once
#include <vector>
#include "BestiaryEntree.h"

class Bestiaire {
private:
    std::vector<BestiaryEntree> entrees;

public:
    void addEntry(const BestiaryEntree& entree);
    void showBestiary() const;
    bool isEmpty() const;
    int  size() const;
};
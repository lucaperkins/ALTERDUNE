#pragma once
#include <string>
#include "Category.h"
#include "Element.h"

class BestiaryEntree {
private:
    std::string monsterName;
    Category category;
    Element element;
    int hpMax;
    int atk;
    int def;
    bool epargne;

public:
    BestiaryEntree(const std::string& monsterName, Category category, const Element& element, int hpMax, int atk, int def, bool epargne);

    const std::string& getMonsterName() const;
    Category getCategory() const;
    const Element& getElement() const;
    int getHpMax() const;
    int getAtk() const;
    int getDef() const;
    bool getEpargne() const;
    void showEntry() const;
};
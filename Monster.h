#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "Element.h"
#include "Category.h"

class Monster : public Entity {
private:
    Category category;
    Element element;
    int mercy;
    int mercyGoal;
    std::vector<std::string> actIds;

public:
    Monster(const std::string& name, Category category, const Element& element,
            int hpMax, int atk, int def, int mercyGoal, const std::vector<std::string>& actIds);
    virtual ~Monster() = default;

    Category getCategory() const;
    const Element& getElement() const;
    int getMercy()     const;
    int getMercyGoal() const;
    const std::vector<std::string>& getActIds() const;

    void changerMercy(int x);
    bool peutEtreEpargne() const;

    virtual int getActCount() const = 0;
    std::string getType() const override;

    void displayStatus() const;
};
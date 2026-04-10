#pragma once

#include "Entity.h"
#include "Inventaire.h"
#include "Element.h"
#include "Item.h"
#include <string>

class Joueur : public Entity {
private:
    int victories;
    int tues;
    int epargnes;
    Inventaire inventaire;
    Element element;

    float atkMultiplier;
    float defMultiplier;

    bool hasActiveBoost;
    std::string boostType;
    float boostValue;
    std::string boostElement;

public:
    Joueur(const std::string& name, int hpMax, int atk, int def, const Element& element);

    int getVictories() const;
    int getTues() const;
    int getEpargnes() const;
    float getAtkMultiplier() const;
    float getDefMultiplier() const;
    const Element& getElement() const;
    Inventaire& getInventaire();

    bool getHasActiveBoost() const;
    const std::string& getBoostType() const;
    float getBoostValue() const;
    const std::string& getBoostElement() const;

    void addVictoire();
    void addTue();
    void addEpargne();
    void addItem(const Item& item);
    void clearBoost();

    void useItem(int i);
    void showStats() const;

    std::string getType() const override;
};
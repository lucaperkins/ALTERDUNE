#include "Joueur.h"
#include <iostream>
#include <algorithm>

using namespace std;

Joueur::Joueur(const string& name, int hpMax, int atk, int def, const Element& element)
    : Entity(name, hpMax, atk, def),
      victories(0),
      tues(0),
      epargnes(0),
      inventaire(),
      element(element),
      atkMultiplier(1.0f),
      defMultiplier(1.0f),
      hasActiveBoost(false),
      boostType(""),
      boostValue(1.0f),
      boostElement("")
{
}

int Joueur::getVictories() const { return victories; }
int Joueur::getTues() const { return tues; }
int Joueur::getEpargnes() const { return epargnes; }
float Joueur::getAtkMultiplier() const { return atkMultiplier; }
float Joueur::getDefMultiplier() const { return defMultiplier; }
const Element& Joueur::getElement() const { return element; }
Inventaire& Joueur::getInventaire() { return inventaire; }
bool Joueur::getHasActiveBoost() const { return hasActiveBoost; }
const string& Joueur::getBoostType() const { return boostType; }
float Joueur::getBoostValue() const { return boostValue; }
const string& Joueur::getBoostElement() const { return boostElement; }

void Joueur::addVictoire() { victories++; }
void Joueur::addTue() { tues++; }
void Joueur::addEpargne() { epargnes++; }

void Joueur::addItem(const Item& item) {
    inventaire.addItem(item);
}

void Joueur::clearBoost() {
    hasActiveBoost = false;
    boostType = "";
    boostValue = 1.0f;
    boostElement = "";
}

void Joueur::useItem(int i) {
    const Item* item = inventaire.useItem(i);
    if (!item) return;

    if (item->getType() == "HEAL") {
        int healed = min(item->getValue(), hpMax - hp);
        hp += healed;

        cout << "Tu utilises " << item->getName()
             << " et recuperes " << healed
             << " HP. (HP: " << hp << "/" << hpMax << ")" << endl;
    }
    else if (item->getType() == "ATK_BOOST" || item->getType() == "DEF_BOOST") {
        hasActiveBoost = true;
        boostType = item->getType();
        boostValue = static_cast<float>(item->getValue());
        boostElement = item->getElement().getName();

        cout << "Tu utilises " << item->getName()
             << " [" << boostElement << "] ! Effet actif." << endl;
    }
}

void Joueur::showStats() const {
    cout << "\n=== Statistiques de " << name << " ===\n"
         << "Element   : " << element.getName() << "\n"
         << "HP        : " << hp << "/" << hpMax << "\n"
         << "ATK       : " << atk << " (x" << atkMultiplier << ")\n"
         << "DEF       : " << def << " (x" << defMultiplier << ")\n"
         << "Victories : " << victories << "/10\n"
         << "Tues      : " << tues << "\n"
         << "Epargnes  : " << epargnes << "\n";

    if (hasActiveBoost) {
        cout << "Boost actif : " << boostType << " [" << boostElement << "]" << endl;
    }
}

string Joueur::getType() const {
    return "Joueur";
}
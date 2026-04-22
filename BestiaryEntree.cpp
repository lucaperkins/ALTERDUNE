#include "BestiaryEntree.h"
#include <iostream>
using namespace std;

/*Cette classe permet d'ajouter un monstre au bestiaire.
il y a une méthode qui permet de voir le statut du monstre*/

BestiaryEntree::BestiaryEntree(const string& monsterName, Category category,
                               const Element& element, int hpMax, int atk, int def, bool epargne) {
    this->monsterName = monsterName;
    this->category = category;
    this->element = element;
    this->hpMax = hpMax;
    this->atk = atk;
    this->def = def;
    this->epargne = epargne;
}

const string& BestiaryEntree::getMonsterName() const { return monsterName; }
Category BestiaryEntree::getCategory() const { return category; }
const Element& BestiaryEntree::getElement() const { return element; }
int BestiaryEntree::getHpMax() const { return hpMax; }
int BestiaryEntree::getAtk() const { return atk; }
int BestiaryEntree::getDef() const { return def; }
bool BestiaryEntree::getEpargne() const { return epargne; }

void BestiaryEntree::showEntry() const {
    cout << " - " << monsterName
         << " [" << CategoryToString(category) << "]"
         << " Element: " << element.getName()
         << " HP: " << hpMax
         << " ATK: " << atk
         << " DEF: " << def
         << " -> " << (epargne ? "Epargne" : "Tue")
         << endl;
}
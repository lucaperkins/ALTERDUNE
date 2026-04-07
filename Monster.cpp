#include "Monster.h"
#include <iostream>
#include <algorithm>
using namespace std;

Monster::Monster(const string& name, Category category, const Element& element,
                 int hpMax, int atk, int def, int mercyGoal,
                 const vector<string>& actIds)
    : Entity(name, hpMax, atk, def),
      category(category), element(element),
      mercy(0), mercyGoal(mercyGoal), actIds(actIds) {}

Category Monster::getCategory() const { return category; }
const Element& Monster::getElement() const { return element; }

int Monster::getMercy() const { return mercy; }

int Monster::getMercyGoal() const { return mercyGoal; }

const vector<string>& Monster::getActIds() const { return actIds; }

void Monster::changerMercy(int x) {
    mercy = max(0, min(mercy + x, mercyGoal));
}

bool Monster::peutEtreEpargne() const {
    return mercy >= mercyGoal;
}

string Monster::getType() const { return "Monster"; }

void Monster::displayStatus() const {
    cout << "  " << name
         << " [" << CategoryToString(category) << "]"
         << " Element: " << element.getName()
         << "  HP: " << hp << "/" << hpMax
         << "  Mercy: " << mercy << "/" << mercyGoal << "\n";
}
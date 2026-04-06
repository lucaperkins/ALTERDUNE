#include "Inventaire.h"
#include <iostream>
using namespace std;

void Inventaire::addItem(const Item& item) {
    items.push_back(item);
}

const Item* Inventaire::useItem(int i) {
    if (i < 0 || i >= (int)items.size()) {
        cout << "  Index invalide.\n";
        return nullptr;
    }
    if (!items[i].use()) {
        cout << "  Plus de " << items[i].getName() << " !\n";
        return nullptr;
    }
    return &items[i];
}

void Inventaire::showItems() const {
    if (isEmpty()) {
        cout << "  Inventaire vide.\n";
        return;
    }
    for (int i = 0; i < (int)items.size(); ++i) {
        cout << "  [" << i << "] ";
        items[i].display();
    }
}

bool Inventaire::isEmpty() const {
    return items.empty();
}
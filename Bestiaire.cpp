#include "Bestiaire.h"
#include <iostream>
using namespace std;

void Bestiaire::addEntry(const BestiaryEntree& entree) {
    entrees.push_back(entree);
}

void Bestiaire::showBestiary() const {
    if (isEmpty()) {
        cout << "  Aucun monstre vaincu pour l'instant.\n";
        return;
    }
    cout << "\n=== Bestiaire ===\n";
    for (const auto& e : entrees) {
        e.showEntry();
    }
}

bool Bestiaire::isEmpty() const {
    return entrees.empty();
}

int Bestiaire::size() const {
    return (int)entrees.size();
}
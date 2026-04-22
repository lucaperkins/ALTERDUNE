#include "Bestiaire.h"
#include <iostream>
using namespace std;

/*C'est la classe qui permet de créer le bestiaire, il y'a une méthode pour ajouter une entité dans le 
bestiaire, une pour voir les monstres du bestiaie, une pour voir si il est vide ou non et enfin, une méthode
pour voir la taille du bestiaire*/

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
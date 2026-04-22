#include "ActAction.h"
#include <iostream>
using namespace std;

/*
    Cette classe représente une action ACT que le joueur peut utiliser en combat.
    Elle permet d’interagir avec le monstre sans attaquer, en modifiant sa jauge de mercy.
*/

ActAction::ActAction(const string& id, const string& text, int mercyImpact) {
    this->id = id;
    this->text = text;
    this->mercyImpact = mercyImpact;
}

const string& ActAction::getId() const { return id; }
const string& ActAction::getText() const { return text; }
int ActAction::getMercyImpact() const { return mercyImpact; }
/*Applique l'action au monstre:
  - affiche le texte
  - modifie la mercy du monstre
  - affiche la réaction du monstre*/
void ActAction::apply(Monster& m) const {
    cout << "\n  >> " << text << "\n";
    m.changerMercy(mercyImpact);
    if (mercyImpact > 0)
        cout << "  [Mercy +" << mercyImpact << "] " << m.getName() << " semble apaisé." << endl;
    else if (mercyImpact < 0)
        cout << "  [Mercy " << mercyImpact << "] " << m.getName() << " est en colère !" << endl;
    else
        cout << "  [Mercy +0] Rien ne change..." << endl;
}
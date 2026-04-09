#include "ActAction.h"
#include <iostream>
using namespace std;

ActAction::ActAction(const string& id, const string& text, int mercyImpact) {
    this->id = id;
    this->text = text;
    this->mercyImpact = mercyImpact;
}

const string& ActAction::getId() const { return id; }
const string& ActAction::getText() const { return text; }
int ActAction::getMercyImpact() const { return mercyImpact; }

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
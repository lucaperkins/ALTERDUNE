#include "Element.h"
using namespace std;

Element::Element(const string& name) : name(name) {
    multipliers["FEU"] = 1.0f;
    multipliers["ACIER"] = 1.0f;
    multipliers["TERRE"] = 1.0f;
    multipliers["ELECTRIQUE"] = 1.0f;
    multipliers["EAU"] = 1.0f;
    multipliers["NEUTRE"] = 1.0f;

    if (name == "FEU") {
        multipliers["ACIER"] = 1.5f; // Bat l'Acier
        multipliers["EAU"]   = 0.5f; // Perd contre l'Eau
    }
    else if (name == "ACIER") {
        multipliers["TERRE"] = 1.5f; // Bat la Terre
        multipliers["FEU"]   = 0.5f; // Perd contre le Feu
    }
    else if (name == "TERRE") {
        multipliers["ELECTRIQUE"] = 1.5f; // Bat la Foudre
        multipliers["ACIER"]  = 0.5f; // Perd contre l'Acier
    }
    else if (name == "ELECTRIQUE") {
        multipliers["EAU"]   = 1.5f; // Bat l'Eau
        multipliers["TERRE"] = 0.5f; // Perd contre la Terre
    }
    else if (name == "EAU") {
        multipliers["FEU"]    = 1.5f; // Bat le Feu
        multipliers["ELECTRIQUE"] = 0.5f; // Perd contre la Foudre
    }
}

string Element::getName() const {
    return name;
}

float Element::getMultiplier(const Element& other) const {
    auto it = multipliers.find(other.getName());
    if (it != multipliers.end())
        return it->second;
    return 1.0f; 
}
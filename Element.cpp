#include "Element.h"
using namespace std;

Element::Element(const string& name) : name(name) {
    if (name == "FEU") {
        multipliers["FEU"] = 1.0f;
        multipliers["EAU"] = 0.5f;   // FEU perd vs EAU
        multipliers["ELECTRIQUE"] = 1.0f;
        multipliers["NEUTRE"] = 1.0f;
    }
    else if (name == "EAU") {
        multipliers["FEU"] = 1.5f;   // EAU bat FEU
        multipliers["EAU"] = 1.0f;
        multipliers["ELECTRIQUE"] = 0.5f;   // EAU perd vs ELECTRIQUE
        multipliers["NEUTRE"] = 1.0f;
    }
    else if (name == "ELECTRIQUE") {
        multipliers["EAU"] = 1.5f;   // ELECTRIQUE bat EAU
        multipliers["FEU"] = 1.0f;
        multipliers["ELECTRIQUE"] = 1.0f;
        multipliers["NEUTRE"] = 1.0f;
    }
    else {  // NEUTRE
        multipliers["FEU"] = 1.0f;
        multipliers["EAU"] = 1.0f;
        multipliers["ELECTRIQUE"] = 1.0f;
        multipliers["NEUTRE"] = 1.0f;
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
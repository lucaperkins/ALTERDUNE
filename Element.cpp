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
        multipliers["ACIER"] = 1.5f; 
        multipliers["EAU"]   = 0.5f; 
    }
    else if (name == "ACIER") {
        multipliers["TERRE"] = 1.5f;
        multipliers["FEU"]   = 0.5f; 
    }
    else if (name == "TERRE") {
        multipliers["ELECTRIQUE"] = 1.5f; 
        multipliers["ACIER"]  = 0.5f; 
    }
    else if (name == "ELECTRIQUE") {
        multipliers["EAU"]   = 1.5f; 
        multipliers["TERRE"] = 0.5f; 
    }
    else if (name == "EAU") {
        multipliers["FEU"]    = 1.5f; 
        multipliers["ELECTRIQUE"] = 0.5f; 
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
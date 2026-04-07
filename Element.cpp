#include "Element.h"

using namespace std;

Element::Element() : name("NEUTRE") {
    multipliers["NORMAL"]= 1.0f;
    multipliers["PLANTE"]= 1.0f;
    multipliers["FEU"] = 1.0f;
    multipliers["EAU"] = 1.0f;
    multipliers["ELECTRIK"] = 1.0f;
    multipliers["GLACE"] = 1.0f;
    multipliers["COMBAT"] = 1.0f;
    multipliers["POISON"] = 1.0f;
    multipliers["SOL"] = 1.0f;
    multipliers["VOL"] = 1.0f;
    multipliers["PSY"] = 1.0f;
    multipliers["INSECTE"] = 1.0f;
    multipliers["ROCHE"] = 1.0f;
    multipliers["SPECTRE"] = 1.0f;
    multipliers["DRAGON"] = 1.0f;
    multipliers["TENEBRES"] = 1.0f;
    multipliers["ACIER"] = 1.0f;
    multipliers["FEE"] = 1.0f;
}

Element::Element(const string& name) : name(name) {
     multipliers["NORMAL"]= 1.0f;
    multipliers["PLANTE"]= 1.0f;
    multipliers["FEU"] = 1.0f;
    multipliers["EAU"] = 1.0f;
    multipliers["ELECTRIK"] = 1.0f;
    multipliers["GLACE"] = 1.0f;
    multipliers["COMBAT"] = 1.0f;
    multipliers["POISON"] = 1.0f;
    multipliers["SOL"] = 1.0f;
    multipliers["VOL"] = 1.0f;
    multipliers["PSY"] = 1.0f;
    multipliers["INSECTE"] = 1.0f;
    multipliers["ROCHE"] = 1.0f;
    multipliers["SPECTRE"] = 1.0f;
    multipliers["DRAGON"] = 1.0f;
    multipliers["TENEBRES"] = 1.0f;
    multipliers["ACIER"] = 1.0f;
    multipliers["FEE"] = 1.0f;

    if (name == "NORMAL") {
        multipliers["ROCHE"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
        multipliers["SPECTRE"] = 0.0f;
    }
    else if (name == "PLANTE") {
        multipliers["EAU"] = 2.0f;
        multipliers["SOL"] = 2.0f;
        multipliers["ROCHE"]=2.0f;
        multipliers["PLANTE"] = 0.5f;
        multipliers["FEU"] = 0.5f;
        multipliers["POISON"] = 0.5f;
        multipliers["VOL"] = 0.5f;
        multipliers["INSECTE"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
        multipliers["DRAGON"] = 0.5f;
    }
    else if (name == "FEU") {
        multipliers["PLANTE"] = 2.0f;
        multipliers["GLACE"] = 2.0f;
        multipliers["ACIER"] = 2.0f;
        multipliers["FEU"] = 0.5f;
        multipliers["EAU"] = 0.5f;
        multipliers["ROCHE"] = 0.5f;
        multipliers["DRAGON"] = 0.5f;
    }
    else if (name == "ELECTRIK") {
        multipliers["EAU"] = 2.0f;
        multipliers["VOL"] = 2.0f;
        multipliers["PLANTE"] = 0.5f;
        multipliers["ELECTRIK"] = 0.5f;
        multipliers["SOL"] = 0.0f;
        multipliers["DRAGON"] = 0.5f;
    }
    else if (name == "GLACE") {
        multipliers["PLANTE"] = 2.0f;
        multipliers["DRAGON"] = 2.0f;
        multipliers["SOL"]= 2.0f;
        multipliers["VOL"]=2.0f;
        multipliers["FEU"] = 0.5f;
        multipliers["EAU"] = 0.5f;
        multipliers["GLACE"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
    }
    else if(name == "COMBAT") {
        multipliers["NORMAL"] = 2.0f;
        multipliers["GLACE"] = 2.0f;
        multipliers["ROCHE"] = 2.0f;
        multipliers["TENEBRES"] = 2.0f;
        multipliers["SPECTRE"] = 0.0f;
        multipliers["POISON"] = 0.5f;
        multipliers["VOL"] = 0.5f;
        multipliers["INSECTE"] = 0.5f;
        multipliers["FEE"] = 0.5f;
        multipliers["PSY"] = 0.5f;
    }
    else if(name == "POISON") 
    {
        multipliers["PLANTE"] = 2.0f;
        multipliers["FEE"] = 2.0f;
        multipliers["POISON"] = 0.5f;
        multipliers["SOL"] = 0.5f;
        multipliers["ROCHE"] = 0.5f;
        multipliers["SPECTRE"] = 0.5f;
        multipliers["ACIER"] = 0.0f;
    }
    else if(name == "SOL") 
    {
        multipliers["FEU"] = 2.0f;
        multipliers["ELECTRIK"] = 2.0f;
        multipliers["ROCHE"] = 2.0f;
        multipliers["POISON"] = 2.0f;
        multipliers["ACIER"] = 2.0f;
        multipliers["VOL"] = 0.0f;
        multipliers["INSECTE"] = 0.5f;
        multipliers["PLANTE"] = 0.5f;
        
    }
    else if(name == "VOL") 
    {
        multipliers["PLANTE"] = 2.0f;
        multipliers["COMBAT"] = 2.0f;
        multipliers["INSECTE"] = 2.0f;
        multipliers["ROCHE"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
        multipliers["ELECTRIK"] = 0.5f;
    }
    else if(name == "PSY") 
    {
        multipliers["COMBAT"] = 2.0f;
        multipliers["POISON"] = 2.0f;
        multipliers["PSY"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
        multipliers["SPECTRE"] = 0.0f;
    }
    else if(name == "INSECTE") 
    {
        multipliers["PLANTE"] = 2.0f;
        multipliers["PSY"] = 2.0f;
        multipliers["TENEBRES"] = 2.0f;
        multipliers["FEU"] = 0.5f;
        multipliers["COMBAT"] = 0.5f;
        multipliers["POISON"] = 0.5f;
        multipliers["VOL"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
        multipliers["FEE"] = 0.5f;
        multipliers["SPECTRE"] = 0.5f;
    }
    else if(name == "ROCHE") 
    {
        multipliers["GLACE"] = 2.0f;
        multipliers["VOL"] = 2.0f;
        multipliers["INSECTE"] = 2.0f;
        multipliers["COMBAT"] = 0.5f;
        multipliers["SOL"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
    }
    else if(name == "SPECTRE") 
    {
        multipliers["PSY"] = 2.0f;
        multipliers["SPECTRE"] = 2.0f;
        multipliers["TENEBRES"] = 0.5f;
        multipliers["NORMAL"] = 0.0f;
    }
    else if(name == "DRAGON") 
    {
        multipliers["DRAGON"] = 2.0f;
        multipliers["ACIER"] = 0.5f;
        multipliers["FEE"] = 0.0f;
    }
    else if(name == "TENEBRES") 
    {
        multipliers["PSY"] = 2.0f;
        multipliers["SPECTRE"] = 2.0f;
        multipliers["COMBAT"] = 0.5f;
        multipliers["TENEBRES"] = 0.5f;
        multipliers["FEE"] = 0.5f;
    }
    else if(name == "ACIER") 
    {
        multipliers["GLACE"] = 2.0f;
        multipliers["ROCHE"] = 2.0f;
        multipliers["FEE"] = 2.0f;
        multipliers["FEU"] = 0.5f;
        multipliers["ELECTRIK"] = 0.5f;
        multipliers["ACIER"] = 0.5f;
        multipliers["PLANTE"] = 0.5f;
    }
    else if(name == "FEE") 
    {
        multipliers["COMBAT"] = 2.0f;
        multipliers["DRAGON"] = 2.0f;
        multipliers["TENEBRES"] = 2.0f;
        multipliers["PLANTE"] = 0.5f;
        multipliers["POISON"] = 0.5f;
        multipliers["ACIER"] = 0.5f;

    }

}

string Element::getName() const {
    return name;
}

float Element::getMultiplier(const Element& other) const {
    auto it = multipliers.find(other.getName());
    if (it != multipliers.end()) {
        return it->second;
    }
    return 1.0f;
}
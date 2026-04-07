#pragma once
#include <string>
#include <map>

class Element {
private:
    std::string name;
    std::map<std::string, float> multipliers;

public:
    Element();
    Element(const std::string& name);

    std::string getName() const;
    float getMultiplier(const Element& other) const;
};
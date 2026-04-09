#pragma once
#include <string>
#include "Monster.h"

class ActAction {
private:
    std::string id;
    std::string text;
    int mercyImpact;

public:
    ActAction(const std::string& id, const std::string& text, int mercyImpact);

    const std::string& getId() const;
    const std::string& getText() const;
    int getMercyImpact() const;

    void apply(Monster& m) const;
};
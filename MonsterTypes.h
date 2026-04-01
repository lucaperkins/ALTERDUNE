#pragma once
#include "Monster.h"

class NormalMonster : public Monster {
public:
    NormalMonster(const std::string& name, const Element& element,
                  int hpMax, int atk, int def, int mercyGoal,
                  const std::vector<std::string>& actIds);
    int getActCount() const override;
    std::string getType() const override;
};

class MiniBoss : public Monster {
public:
    MiniBoss(const std::string& name, const Element& element,
             int hpMax, int atk, int def, int mercyGoal,
             const std::vector<std::string>& actIds);
    int getActCount() const override;
    std::string getType() const override;
};

class Boss : public Monster {
public:
    Boss(const std::string& name, const Element& element,
         int hpMax, int atk, int def, int mercyGoal,
         const std::vector<std::string>& actIds);
    int getActCount() const override;
    std::string getType() const override;
};
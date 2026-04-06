#include "MonsterTypes.h"
using namespace std;

// ── NormalMonster ──────────────────────────────────────────────────────────
NormalMonster::NormalMonster(const string& name, const Element& element,
                             int hpMax, int atk, int def, int mercyGoal,
                             const vector<string>& actIds)
    : Monster(name, Category::NormalMonster, element,
              hpMax, atk, def, mercyGoal, actIds) {}

int    NormalMonster::getActCount() const { return 2; }
string NormalMonster::getType()     const { return "NormalMonster"; }

// ── MiniBoss ───────────────────────────────────────────────────────────────
MiniBoss::MiniBoss(const string& name, const Element& element,
                   int hpMax, int atk, int def, int mercyGoal,
                   const vector<string>& actIds)
    : Monster(name, Category::MiniBoss, element,
              hpMax, atk, def, mercyGoal, actIds) {}

int    MiniBoss::getActCount() const { return 3; }
string MiniBoss::getType()     const { return "MiniBoss"; }

// ── Boss ───────────────────────────────────────────────────────────────────
Boss::Boss(const string& name, const Element& element,
           int hpMax, int atk, int def, int mercyGoal,
           const vector<string>& actIds)
    : Monster(name, Category::Boss, element,
              hpMax, atk, def, mercyGoal, actIds) {}

int    Boss::getActCount() const { return 4; }
string Boss::getType()     const { return "Boss"; }
#include "Category.h"
using namespace std;
/* classe qui définit les catégories de monstres */
std::string CategoryToString(Category type) {
    switch (type) {
        case Category::Boss: return "Boss";
        case Category::MiniBoss: return "MiniBoss";
        case Category::NormalMonster: return "NormalMonster";
        default: return "Inconnu";
    }
}

Category stringToCategory(const std::string& str) {
    if (str == "Boss") return Category::Boss;
    if (str == "MiniBoss") return Category::MiniBoss;
    if (str == "NormalMonster") return Category::NormalMonster;
    return Category::Inconnu;
}
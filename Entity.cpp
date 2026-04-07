#include "Entity.h"
#include <algorithm>
using namespace std;

Entity::Entity(const string& name, int hpMax, int atk, int def)
    {
    this->name = name;
    this->hpMax = hpMax;
    this->hp = hpMax; // HP initialisé à HP max
    this->atk = atk;
    this->def = def;

    }

string Entity:: getName() const { return name;}

int Entity::getHp() const {return hp;}

int Entity::getHpMax() const {return hpMax;}

int Entity::getAtk() const {return atk;}

int Entity::getDef() const {return def;}

void Entity::takeDamage(int dmg) 
{
    if(hp <= 0)
    {
        hp = 0;
        return;
    }  
    hp = hp-dmg;
    return;
}

bool Entity::isAlive() const 
{
    if(hp <= 0)
    {
        return false;
    }
    return true;
}
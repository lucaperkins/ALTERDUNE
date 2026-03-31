#pragma once
#include <string>

class Entity {
protected:
    std::string name;   // std:: obligatoire
    int hp;
    int hpMax;
    int atk;
    int def;

public:
    Entity(const std::string& name, int hpMax, int atk, int def);
    virtual ~Entity() = default;

    std::string getName() const;  
    int getHp()    const;
    int getHpMax() const;
    int getAtk()   const;
    int getDef()   const;

    void takeDamage(int dmg);
    bool isAlive() const;

    virtual std::string getType() const = 0;
};
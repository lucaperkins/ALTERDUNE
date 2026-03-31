#include <string>
 
using namespace std; 

class Entity {
protected:
    string name;
    int hp;
    int hpMax;
    int atk;
    int def;
 
public:
    Entity(const std::string& name, int hpMax, int atk, int def);
    virtual ~Entity() = default;
 
    string getName() const;
    int getHp() const;
    int getHpMax() const;
    int getAtk() const;
    int getDef() const;
 
    void takeDamage(int dmg);
    bool isAlive() const;
 
    virtual string getType() const = 0;
};
 
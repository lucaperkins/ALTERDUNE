#include <string>
 
using namespace std; 

class Entity {
protected:
    string name;
    int hp;
    int hpMax;
 
public:
    Entity(const string& name, int hpMax);
    virtual ~Entity() = default;
 
    string getName() const;
    int getHp() const;
    int getHpMax() const;
 
    void takeDamage(int dmg);
    bool isAlive() const;
 
    // Méthode virtuelle pure -> classe abstraite
    virtual string getType() const = 0;
};
 
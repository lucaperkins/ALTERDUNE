#include "Item.h"
#include <iostream>
using namespace std;

Item::Item(const string& name, const string& type, int value, int quantity):name(name), type(type), value(value), quantity(quantity){}

string Item::getName()const{
    return name; 
    }
string Item::getType()const{
    return type; 
    }
int Item::getValue()const{
    return value; 
    }
int Item::getQuantity()const{
    return quantity; 
    }

bool Item::use() {
    if (quantity <= 0) return false;
    --quantity;
    return true;
}

void Item::display() const {
    cout << "  [" << name << "] x" << quantity << "  -> Soigne " << value << " HP" << endl;
}
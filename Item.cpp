#include "Item.h"
#include <iostream>
using namespace std;

Item::Item(const string& name, const string& type, int value, int quantity, const Element& element):name(name), type(type), value(value), quantity(quantity), element(element){}

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

const Element Item::getElement()const{
    return element;
}

bool Item::use() {
    if (quantity <= 0) return false;
    --quantity;
    return true;
}

void Item::display() const {
    cout << "  [" << name << "] x" << quantity << " Element : " << element.getName() << " Type : " << type << endl;
}
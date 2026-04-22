#include "Item.h"
#include <iostream>
using namespace std;

/*Cette classe permet de gérer les items. Il y a une méthode qui sert à utiliser un item et une méthode d'affichage
qui permet au joueur de comprendre combien d'item lui reste t'il, de quel type et à quelle catégorie l'item appartient*/

Item::Item(const string& name, const string& type, int value, int quantity, const Element& element)
{
    this->name = name;
    this->type = type;
    this->value = value;
    this->quantity = quantity;
    this->element = element;

}

string Item::getName()const{return name; }

string Item::getType()const{return type; }

int Item::getValue()const{return value; }

int Item::getQuantity()const{return quantity;}

const Element& Item::getElement()const{return element;}

bool Item::use() {
    if (quantity <= 0) 
    {
        return false;
    }
    quantity--;
    return true;
}

void Item::display() const {
    cout << "  [" << name << "] x" << quantity << " Element : " << element.getName() << " Type : " << type << endl;
}
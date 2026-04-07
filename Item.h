#pragma once
#include <string>
#include "Element.h"

class Item {
    private:
        std::string name;
        std::string type;
        int value;
        int quantity;
        Element element;
    public:
        Item(const std::string& name, const std::string& type, int value, int quantity, const Element& element);
        std::string getName() const;
        std::string getType() const;
        int getValue() const;
        int getQuantity() const;
        const Element& getElement() const;
        bool use();
        void display() const;
};
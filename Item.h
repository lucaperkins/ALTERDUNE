#pragma once
#include <string>

class Item {
    private:
        std::string name;
        std::string type;
        int value;
        int quantity;
    public:
        Item(const std::string& name, const std::string& type, int value, int quantity);
        std::string getName() const;
        std::string getType() const;
        int getValue() const;
        int getQuantity() const;
        bool use();
        void display() const;
};
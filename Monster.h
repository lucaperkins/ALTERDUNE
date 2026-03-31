#pragma once
#include <string>
#include "Entity.h"
#include "Element.h"
#include "Category.h"

class Monster : public Entity{
protected:    
    Element element;
    Category category;
    int mercy;
    int mercyGoal;
    //std::vector <> actIds;
public:
    int getMercy() const;
    int getMercyGoal() const;
    
};
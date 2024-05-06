#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Zombie : public GameObject {
public :
    Zombie (int ,int ,SpriteType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
protected : 
    int freeze_time ; 
    
};

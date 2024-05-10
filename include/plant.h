#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Plant : public GameObject {
public :
    Plant (int ,int ,SpriteType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
protected : 
    int damage ,health ,hit_rate;
};

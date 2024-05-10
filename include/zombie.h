#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Zombie : public GameObject {
public :
    Zombie (int ,int ,SpriteType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ;
    void move(double) ; 
    Clock last_move_clock ; 
protected : 
    int freeze_time ;
    int speed ,damage ,hit_rate ,health; 
};

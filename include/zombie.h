#pragma once 

#include "game_object.h"

class Zombie : public GameObject {
public :
    virtual void render() = 0 ; 
    virtual void update() = 0 ; 
protected : 
    int freeze_time ; 
};

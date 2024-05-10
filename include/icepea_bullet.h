#pragma once 

#include "global_stuff.h"
#include "bullet.h"

class Icepea_Bullet : public Bullet {
public :
    Icepea_Bullet (int ,int ,BulletType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
protected : 
    
};
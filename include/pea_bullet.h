#pragma once 

#include "global_stuff.h"
#include "bullet.h"

class Pea_Bullet : public Bullet {
public :
    Pea_Bullet (int ,int ,BulletType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
    void move(double) ; 
private : 
    
};
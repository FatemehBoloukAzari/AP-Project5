#pragma once 

#include "global_stuff.h"
#include "bullet.h"

class Mellon_Bullet : public Bullet {
public :
    Mellon_Bullet (int ,int ,BulletType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
private : 
    void move(double) ; 
};
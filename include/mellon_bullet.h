#pragma once 

#include "global_stuff.h"
#include "bullet.h"

class Mellon_Bullet : public Bullet {
public :
    Mellon_Bullet (int ,double ,double ,BulletType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
    virtual void move(double) ;
    virtual int get_damage() ;
private : 
};
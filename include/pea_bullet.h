#pragma once 

#include "global_stuff.h"
#include "bullet.h"

class Pea_Bullet : public Bullet {
public :
    Pea_Bullet (int ,double ,double ,BulletType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
    virtual void move(double) ;
    virtual int get_damage() ;
private : 
    
};
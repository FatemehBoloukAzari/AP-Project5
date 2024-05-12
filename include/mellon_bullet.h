#pragma once 

#include "global_stuff.h"
#include "bullet.h"
#include "zombie.h"

class Mellon_Bullet : public Bullet {
public :
    Mellon_Bullet (int ,double ,double ,BulletType, Zombie*);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ; 
    virtual void move(double) ;
    virtual int get_damage() ;
    bool end_collision_time();
    Zombie* get_target_zombie() {return target_zombie;}
private : 
    Zombie* target_zombie;
    double init_x;
    double init_y;
    double collision_time;
    Clock shooting_time;
};
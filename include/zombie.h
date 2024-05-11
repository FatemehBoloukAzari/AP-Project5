#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Zombie : public GameObject {
public :
    Zombie (int ,int ,SpriteType);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ;
    virtual bool is_plant() ; 
    void move(double) ; 
    void init_hit_clock() ; 
    Clock last_move_clock ,last_hit_clock; 
    bool moving ,attacked ;
    int get_column_number(double ,double) ; 
    int get_damage(); 
private : 
    int freeze_time ;
    int speed ,damage ,hit_rate ,health;
};

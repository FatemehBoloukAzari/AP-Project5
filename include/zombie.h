#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Zombie : public GameObject {
public :
    Zombie (double ,double ,SpriteType ,int);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ;
    virtual bool is_plant() ; 
    void move(double) ; 
    void init_hit_clock() ; 
    void decrease_health(int); 
    void affect_freezing(); 
    Clock last_move_clock ,last_hit_clock ,freeze_clock; 
    bool moving ,attacked ;
    int get_column_number(double) ; 
    int get_damage(); 
    int get_row(){return row;} 
    FloatRect get_rect(); 
    bool freezed ; 
    bool is_dead(); 
    int get_speed() {return speed;}
private : 
    int freeze_time ,row ;
    int speed ,damage ,hit_rate ,health;
    Music frozen_sound ; 
};

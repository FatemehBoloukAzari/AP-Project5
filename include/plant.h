#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Plant : public GameObject {
public :
    Plant (double ,double ,SpriteType ,int ,int);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ;  
    virtual bool is_plant() ;
    void decrease_health(int); 
    void init_shot_clock(); 
    bool is_dead(); 
    int get_row() ;
    int get_column() ; 
    bool shooting ,shooted ; 
    SpriteType get_sprite_type() ; 
private : 
    int health ,hit_rate ,row ,column ;
    Clock last_shot_clock ; 
    SpriteType sprite_type ; 
};

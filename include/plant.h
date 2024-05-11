#pragma once 

#include "global_stuff.h"
#include "game_object.h"

class Plant : public GameObject {
public :
    Plant (int ,int ,SpriteType ,int ,int);
    virtual void render(RenderWindow &window) ; 
    virtual void update() ;  
    virtual bool is_plant() ;
    void decrease_health(int); 
    bool is_dead(); 
    int get_row() ;
    int get_column() ; 
private : 
    int damage ,health ,hit_rate ,row ,column ;
    Clock last_shot_clock ; 
};

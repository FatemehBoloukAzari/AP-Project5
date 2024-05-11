#pragma once 

#include "global_stuff.h"

class GameObject {
public :
	GameObject (double ,double ,SpriteType) ; 
	double get_x() {return x;}
	virtual void update() = 0 ; 
	virtual void render(RenderWindow &window) = 0 ;
	virtual bool is_plant() = 0 ; 
protected :
	int health ;
	double x ,y ;
	Clock last_damage;
	Texture item_texture;
    Sprite item_sprite;
    SpriteType sprite_type;
};

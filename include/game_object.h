#pragma once 

#include "global_stuff.h"

class GameObject {
public :
	GameObject (double ,double ,SpriteType) ; 
	virtual void update() = 0 ; 
	virtual void render(RenderWindow &window) = 0 ;
protected :
	int health ;
	double x ,y ;
	int time_since_last_damage ;
	Texture item_texture;
    Sprite item_sprite;
    SpriteType sprite_type;
};

#pragma once 

#include "global_stuff.h"

class Bullet {
public :
	Bullet (double ,double ,BulletType) ; 
	virtual void update() = 0 ; 
	virtual void render(RenderWindow &window) = 0 ;
protected :
	double x ,y ;
	Texture item_texture;
    Sprite item_sprite;
    BulletType bullet_type;
};
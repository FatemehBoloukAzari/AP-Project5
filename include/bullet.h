#pragma once 

#include "global_stuff.h"
#include "setting.h"

class Bullet {
public :
	Bullet (double ,double ,BulletType) ; 
	virtual void update() = 0 ; 
	virtual void render(RenderWindow &window) = 0 ;
	virtual void move() = 0 ;
	virtual int get_damage() = 0 ;
protected :
	double x ,y ;
	int speed ,damage ; 
	Clock last_move_clock ; 
	Texture item_texture;
    Sprite item_sprite;
    BulletType bullet_type;
};
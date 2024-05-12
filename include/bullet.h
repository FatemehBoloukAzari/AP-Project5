#pragma once 

#include "global_stuff.h"
#include "setting.h"

class Bullet {
public :
	Bullet (int ,double ,double ,BulletType) ; 
	virtual void update() = 0 ; 
	virtual void render(RenderWindow &window) = 0 ;
	virtual void move(double) = 0 ;
	virtual int get_damage() = 0 ;
	BulletType get_bullet_type(){return bullet_type;}; 
	bool exited_screen() ; 
	int get_row(){return row;}
	double get_x(){return x;}
	double get_y(){return y;}
	FloatRect get_rect(){return item_sprite.getLocalBounds();} 
protected :
	double y ,x;
	int speed ,damage ,row ; 
	Clock last_move_clock ; 
	Texture item_texture;
    Sprite item_sprite;
    BulletType bullet_type;
};
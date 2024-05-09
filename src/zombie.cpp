#include "zombie.h"

const int REGULAR_WIDTH = 110;
const int REGULAR_HEIGHT = 180; 
const int HAIRMETALGARGANTUAR_WIDTH = 240; 
const int HAIRMETALGARGANTUAR_HEIGHT = 250; 
int ZOMBIE_MOVE_INTERVAL = 30 ; 
int ZOMBIE_SPEED = 50 ; 

void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << H ;
	debug_out(T...);
}
 
#define debug(...)             cerr << "(" << #__VA_ARGS__ << "): ", debug_out(__VA_ARGS__)

Zombie::Zombie(int _x ,int _y ,SpriteType _sprite_type) : GameObject(_x ,_y ,_sprite_type){
    freeze_time = 0 ; 
}

void Zombie::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    switch (sprite_type){
    case REGULAR:
        scale_x = (double)REGULAR_WIDTH / item_texture.getSize().x;
        scale_y = (double)REGULAR_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case HAIRMETALGARGANTUAR:
        scale_x = (double)HAIRMETALGARGANTUAR_WIDTH / item_texture.getSize().x;
        scale_y = (double)HAIRMETALGARGANTUAR_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    default:
        break;
    }
    
}

void Zombie::move(double change_amount){
    x -= change_amount ;
}

void Zombie::update(){
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= ZOMBIE_MOVE_INTERVAL)
    {
        move((double)ZOMBIE_SPEED / 100);
        last_move_clock.restart();
    }
}


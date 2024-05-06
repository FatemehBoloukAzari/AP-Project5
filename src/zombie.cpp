#include "zombie.h"

const int REGULAR_WIDTH = 110;
const int REGULAR_HEIGHT = 180; 
const int HAIRMETALGARGANTUAR_WIDTH = 250; 
const int HAIRMETALGARGANTUAR_HEIGHT = 260; 

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

void Zombie::update(){

}


#include "plant.h"

const int SUNFLOWER_WIDTH = 120;
const int SUNFLOWER_HEIGHT = 125; 
const int PEASHOOTER_WIDTH = 120; 
const int PEASHOOTER_HEIGHT = 125; 
const int SNOWPEA_WIDTH = 135; 
const int SNOWPEA_HEIGHT = 125; 
const int WALNUT_WIDTH = 120; 
const int WALNUT_HEIGHT = 139; 
const int MELONPULT_WIDTH = 200; 
const int MELONPULT_HEIGHT = 140; 

Plant::Plant(int _x ,int _y ,SpriteType _sprite_type) : GameObject(_x ,_y ,_sprite_type){}

void Plant::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    switch (sprite_type){
    case SUNFLOWER:
        scale_x = (double)SUNFLOWER_WIDTH / item_texture.getSize().x;
        scale_y = (double)SUNFLOWER_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case PEASHOOTER:
        scale_x = (double)PEASHOOTER_WIDTH / item_texture.getSize().x;
        scale_y = (double)PEASHOOTER_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case SNOWPEA:
        scale_x = (double)SNOWPEA_WIDTH / item_texture.getSize().x;
        scale_y = (double)SNOWPEA_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case WALNUT: 
        scale_x = (double)WALNUT_WIDTH / item_texture.getSize().x;
        scale_y = (double)WALNUT_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case MELONPULT:
        scale_x = (double)MELONPULT_WIDTH / item_texture.getSize().x;
        scale_y = (double)MELONPULT_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    default:
        break;
    }
    
}

void Plant::update(){

}


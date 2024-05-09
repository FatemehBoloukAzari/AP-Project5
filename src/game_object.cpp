#include "game_object.h"

GameObject::GameObject(double _x ,double _y ,SpriteType _sprite_type){
    x = _x ; 
    y = _y ; 
    sprite_type = _sprite_type ;
    switch (sprite_type){
        case WALNUT:
            item_texture.loadFromFile(PICS_PATH + "defai.png");
            break;
        case PEASHOOTER:
            item_texture.loadFromFile(PICS_PATH + "nokhode_shooti.png");
            break;
        case SNOWPEA:
            item_texture.loadFromFile(PICS_PATH + "nokhode_barfi.png");
            break;
        case MELONPULT:
            item_texture.loadFromFile(PICS_PATH + "hendevane_part_kon.png");
            break;
        case SUNFLOWER:
            item_texture.loadFromFile(PICS_PATH + "aftab_gardoon.png");           
            break;
        case REGULAR: 
            item_texture.loadFromFile(PICS_PATH + "zombie_adi.png"); 
            break ; 
        case HAIRMETALGARGANTUAR:
            item_texture.loadFromFile(PICS_PATH + "giant.png");
            break ; 
        default:
            break;
    }
    item_sprite.setTexture(item_texture);
}
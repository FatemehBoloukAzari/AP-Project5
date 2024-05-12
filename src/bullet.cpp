#include "bullet.h"
#include "setting.h"

Bullet::Bullet(int _row ,double _x ,double _y ,BulletType _bullet_type){
    x = _x ;
    y = _y ; 
    row = _row ; 
    bullet_type = _bullet_type ; 
    item_sprite.setOrigin(item_sprite.getLocalBounds().width / 2, item_sprite.getLocalBounds().height / 2);
    switch (bullet_type){
        case PEA:
            speed = read_plant_speed_from_file(PEASHOOTER) ; 
            damage = read_plant_damage_from_file(PEASHOOTER) ; 
            item_texture.loadFromFile(PICS_PATH + "pea-shooter-bullet.png");
            break;
        case ICEPEA:
            speed = read_plant_speed_from_file(SNOWPEA) ; 
            damage = read_plant_damage_from_file(SNOWPEA) ; 
            item_texture.loadFromFile(PICS_PATH + "snow-pea-bullet.png");
            break;
        case MELLON:
            speed = read_plant_speed_from_file(MELONPULT) ; 
            damage = read_plant_damage_from_file(MELONPULT) ; 
            item_texture.loadFromFile(PICS_PATH + "melonpult_melon.png");
            break;
        default:
            break;
    }
    item_sprite.setTexture(item_texture);
}

bool Bullet::exited_screen(){
    if (x > WIDTH)
        return true;
    return false;
}

#include "bullet.h"

Bullet::Bullet(double _x ,double _y ,BulletType _bullet_type){
    x = _x ; 
    y = _y ; 
    bullet_type = _bullet_type ; 
    switch (bullet_type){
        case PEA:
            item_texture.loadFromFile(PICS_PATH + "pea-shooter-bullet.png");
            break;
        case ICEPEA:
            item_texture.loadFromFile(PICS_PATH + "snow-pea-bullet.png");
            break;
        case MELLON:
            item_texture.loadFromFile(PICS_PATH + "melonpult_melon.png");
            break;
        default:
            break;
    }
    item_sprite.setTexture(item_texture);
}
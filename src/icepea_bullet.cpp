#include "icepea_bullet.h"

Icepea_Bullet::Icepea_Bullet(int _x ,int _y ,BulletType _bullet_type) : Bullet(_x ,_y ,_bullet_type){
}

void Icepea_Bullet::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    scale_x = (double)PEA_BULLET_WIDTH / item_texture.getSize().x;
    scale_y = (double)PEA_BULLET_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setPosition(x, y);
    window.draw(item_sprite);
}

void Icepea_Bullet::update(){

}
#include "pea_bullet.h"

Pea_Bullet::Pea_Bullet(int _x ,int _y ,BulletType _bullet_type) : Bullet(_x ,_y ,_bullet_type){
}

void Pea_Bullet::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    scale_x = (double)PEA_BULLET_WIDTH / item_texture.getSize().x;
    scale_y = (double)PEA_BULLET_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setPosition(x, y);
    window.draw(item_sprite);
}

void Pea_Bullet::move(double change_amount){
    x += change_amount ; 
}

void Pea_Bullet::update(){
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= PEA_BULLET_MOVE_INTERVAL)
    {
        move((double)speed / 100);
        last_move_clock.restart();
    }
}
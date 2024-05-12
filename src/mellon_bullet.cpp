#include "mellon_bullet.h"

Mellon_Bullet::Mellon_Bullet(int row ,double _x ,double _y ,BulletType _bullet_type) : Bullet(row ,_x ,_y ,_bullet_type){
    damage = read_plant_damage_from_file(MELONPULT) ; 
    speed = read_plant_speed_from_file(MELONPULT) ;
}

void Mellon_Bullet::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    scale_x = (double)MELLON_BULLET_WIDTH / item_texture.getSize().x;
    scale_y = (double)MELLON_BULLET_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setPosition(x, y);
    window.draw(item_sprite);
}

void Mellon_Bullet::update(){
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= ICEPEA_BULLET_MOVE_INTERVAL)
    {
        move((double)speed / 100);
        last_move_clock.restart();
    }
}

void Mellon_Bullet::move(double change_amount){
    x += change_amount ; 
}

int Mellon_Bullet::get_damage(){
    return damage;
}
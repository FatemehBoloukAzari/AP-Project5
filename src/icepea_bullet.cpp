#include "icepea_bullet.h"

Icepea_Bullet::Icepea_Bullet(int _x ,int _y ,BulletType _bullet_type) : Bullet(_x ,_y ,_bullet_type){
    damage = read_plant_damage_from_file(SNOWPEA) ; 
    speed = read_plant_speed_from_file(SNOWPEA) ;
}

void Icepea_Bullet::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    scale_x = (double)PEA_BULLET_WIDTH / item_texture.getSize().x;
    scale_y = (double)PEA_BULLET_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setPosition(x, y);
    window.draw(item_sprite);
}

void Icepea_Bullet::move(double change_amount){
    x += change_amount ; 
}

int Icepea_Bullet::get_damage(){
    return damage;
}

void Icepea_Bullet::update(){
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= ICEPEA_BULLET_MOVE_INTERVAL)
    {
        move((double)speed / 100);
        last_move_clock.restart();
    }
}
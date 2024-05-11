#include "mellon_bullet.h"

Mellon_Bullet::Mellon_Bullet(int _x ,int _y ,BulletType _bullet_type) : Bullet(_x ,_y ,_bullet_type){
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

}

void Mellon_Bullet::move(double){
}

int Mellon_Bullet::get_damage(){
    return damage;
}

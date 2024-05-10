#include "zombie.h" 
#include "setting.h" 

Zombie::Zombie(int _x ,int _y ,SpriteType _sprite_type) : GameObject(_x ,_y ,_sprite_type){
    freeze_time = 0 ; 
    switch (sprite_type){
    case REGULAR:
        speed = read_zombie_speed_from_file(REGULAR) ; 
        damage = read_zombie_damage_from_file(REGULAR) ;
        hit_rate = read_zombie_hit_rate_from_file(REGULAR) ; 
        health = read_zombie_health_from_file(REGULAR) ; 
        break;
    case HAIRMETALGARGANTUAR:
        speed = read_zombie_speed_from_file(HAIRMETALGARGANTUAR) ; 
        damage = read_zombie_damage_from_file(HAIRMETALGARGANTUAR) ;
        hit_rate = read_zombie_hit_rate_from_file(HAIRMETALGARGANTUAR) ; 
        health = read_zombie_health_from_file(HAIRMETALGARGANTUAR) ; 
        break;
    default:
        break;
    }
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

void Zombie::move(double change_amount){
    x -= change_amount ;
}

void Zombie::update(){
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= ZOMBIE_MOVE_INTERVAL)
    {
        move((double)speed / 100);
        last_move_clock.restart();
    }
}


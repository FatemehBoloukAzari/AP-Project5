#include "zombie.h" 
#include "setting.h" 

Zombie::Zombie(int _x ,int _y ,SpriteType _sprite_type) : GameObject(_x ,_y ,_sprite_type){
    freeze_time = 0 ; 
    moving = true ; 
    attacked = false ; 
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

int Zombie::get_column_number(double scale_x ,double scale_y){
    int ptr = 0; 
    while (ptr < NUM_COLUMN && scale_x * field_square_x[ptr] < x + ZOMBIE_EATING_MARGIN) ptr++ ; 
    return ptr ; 
}

void Zombie::move(double change_amount){
    x -= change_amount ;
}

void Zombie::init_hit_clock(){
    last_hit_clock.restart() ; 
}

bool Zombie::is_plant(){
    return false ; 
}

void Zombie::update(){
    if (moving){
        Time elapsed = last_move_clock.getElapsedTime();
        if (elapsed.asMilliseconds() >= ZOMBIE_MOVE_INTERVAL)
        {
            move((double)speed / 100);
            last_move_clock.restart();
        }
    }
    else {
        Time elapsed = last_hit_clock.getElapsedTime();
        if (elapsed.asSeconds() >= hit_rate)
        {
            attacked = true ; 
            last_hit_clock.restart();
        }
    }
}

int Zombie::get_damage(){
    return damage ; 
}
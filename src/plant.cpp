#include "plant.h"
#include "setting.h"

Plant::Plant(double _x ,double _y ,SpriteType _sprite_type ,int _row ,int _column) : GameObject(_x ,_y ,_sprite_type)
{ 
    sprite_type = _sprite_type ; 
    shooted = false ; 
    shooting = false ; 
    row = _row ; 
    column = _column ;
    item_sprite.setOrigin(item_sprite.getLocalBounds().width / 2, item_sprite.getLocalBounds().height / 2);
    switch (sprite_type){
    case PEASHOOTER:
        sprite_type = PEASHOOTER ;
        hit_rate = read_plant_hit_rate_from_file(PEASHOOTER) ; 
        health = read_plant_health_from_file(PEASHOOTER) ;
        break;
    case SNOWPEA:
        sprite_type = SNOWPEA ;
        hit_rate = read_plant_hit_rate_from_file(SNOWPEA) ; 
        health = read_plant_health_from_file(SNOWPEA) ; 
        break;
    case MELONPULT:
        sprite_type = MELONPULT ;
        hit_rate = read_plant_hit_rate_from_file(MELONPULT) ; 
        health = read_plant_health_from_file(MELONPULT) ; 
        break;
    case SUNFLOWER:
        sprite_type = SUNFLOWER ;
        hit_rate = read_plant_hit_rate_from_file(SUNFLOWER) ; 
        health = read_plant_health_from_file(SUNFLOWER) ; 
        break;
    case WALNUT:
        sprite_type = WALNUT ;
        hit_rate = read_plant_hit_rate_from_file(WALNUT) ; 
        health = read_plant_health_from_file(WALNUT) ; 
        break;
    default:
        break;
    }
}

void Plant::render(RenderWindow &window){ 
    double scale_x ,scale_y ; 
    switch (sprite_type){
    case SUNFLOWER:
        scale_x = (double)SUNFLOWER_WIDTH / item_texture.getSize().x;
        scale_y = (double)SUNFLOWER_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case PEASHOOTER:
        scale_x = (double)PEASHOOTER_WIDTH / item_texture.getSize().x;
        scale_y = (double)PEASHOOTER_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y); 
        window.draw(item_sprite);
        break;
    case SNOWPEA:
        scale_x = (double)SNOWPEA_WIDTH / item_texture.getSize().x;
        scale_y = (double)SNOWPEA_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case WALNUT: 
        scale_x = (double)WALNUT_WIDTH / item_texture.getSize().x;
        scale_y = (double)WALNUT_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    case MELONPULT:
        scale_x = (double)MELONPULT_WIDTH / item_texture.getSize().x;
        scale_y = (double)MELONPULT_HEIGHT / item_texture.getSize().y;
        item_sprite.setScale(scale_x, scale_y);
        item_sprite.setPosition(x, y);
        window.draw(item_sprite);
        break;
    default:
        break;
    }
    
}

void Plant::decrease_health(int damage){
    health -= damage ; 
}

void Plant::init_shot_clock(){
    last_shot_clock.restart() ; 
}

bool Plant::is_dead(){
    return health <= 0; 
}

int Plant::get_row(){
    return row ; 
}

int Plant::get_column(){
    return column ;
}

SpriteType Plant::get_sprite_type(){
    return sprite_type;
}

bool Plant::is_plant(){
    return true ; 
}

void Plant::update(){
    if(shooting) { 
        Time elapsed = last_shot_clock.getElapsedTime();
        if (elapsed.asSeconds() >= hit_rate)
        {
            shooted = true ; 
            last_shot_clock.restart();
        }
    }
}


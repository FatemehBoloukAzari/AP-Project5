#include "plant.h"
#include "setting.h"

Plant::Plant(int _x ,int _y ,SpriteType _sprite_type ,int _row ,int _column) : GameObject(_x ,_y ,_sprite_type)
{
    row = _row ; 
    column = _column ;
    item_sprite.setOrigin(item_sprite.getLocalBounds().width / 2, item_sprite.getLocalBounds().height / 2);
    switch (sprite_type){
    case PEASHOOTER:
        damage = read_plant_damage_from_file(PEASHOOTER) ;
        hit_rate = read_plant_hit_rate_from_file(PEASHOOTER) ; 
        health = read_plant_health_from_file(PEASHOOTER) ;
        break;
    case SNOWPEA:
        damage = read_plant_damage_from_file(SNOWPEA) ;
        hit_rate = read_plant_hit_rate_from_file(SNOWPEA) ; 
        health = read_plant_health_from_file(SNOWPEA) ; 
        break;
    case MELONPULT:
        damage = read_plant_damage_from_file(MELONPULT) ;
        hit_rate = read_plant_hit_rate_from_file(MELONPULT) ; 
        health = read_plant_health_from_file(MELONPULT) ; 
        break;
    case SUNFLOWER:
        damage = read_plant_damage_from_file(SUNFLOWER) ;
        hit_rate = read_plant_hit_rate_from_file(SUNFLOWER) ; 
        health = read_plant_health_from_file(SUNFLOWER) ; 
        break;
    case WALNUT:
        damage = read_plant_damage_from_file(WALNUT) ;
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

bool Plant::is_dead(){
    return health <= 0; 
}

int Plant::get_row(){
    return row ; 
}

int Plant::get_column(){
    return column ;
}

bool Plant::is_plant(){
    return true ; 
}

void Plant::update(){

}


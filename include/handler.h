#pragma once

#include "global_stuff.h"
#include "menu.h"
#include "zombie.h"
#include "sun.h"
#include "plant.h"
#include "bullet.h"
#include "mellon_bullet.h" 
#include "pea_bullet.h"
#include "icepea_bullet.h"

class Handler
{
public:
    Handler();
    void update(State &state, double scale_x ,double scale_y);
    void render(RenderWindow &window);
    void add_zombie(SpriteType ,double ,double ,int);
    void add_bullet(BulletType ,int ,double ,double); 
    void generate_zombie();
    void handle_mouse_press(Event event, double, double);
    SpriteType get_random_zombie_type();
    void main_menu_render(RenderWindow &window);
    void game_over_render(RenderWindow &window);
    void victory_render(RenderWindow &window);
    void in_game_initialization();
    void handle_plants_shooting(); 
    void game_over_initialization();
    void handle_zombie_damages(double ,double); 
    void clean_dead_plants(); 
    void check_moving_stopped_zombies(double ,double); 
    bool is_in_same_field(Zombie* ,Plant* ,double ,double); 
    //~Handler();
private:
    bool square_is_full[NUM_ROW][NUM_COLUMN];
    int zombie_amount_per_cycle ,giant_probability; 
    int zombie_cycle_time ,zombie_generate_duration ,zombie_increase_rate; 
    Clock clock ,last_zombie_increase_clock ,last_zombie_spawn_clock;
    vector <GameObject*> game_objects;
    vector <Sun*> suns;
    vector <Bullet*> bullets;
    vector <Zombie*> zombies_in_line[5]; 
    vector <Bullet*> bullets_in_line[5]; 
    Menu menu;
    Clock sun_generating_clock;
    Clock game_over_clock;
    int number_of_suns;
    int sun_interval;
    void render_sun_bank(RenderWindow &window);
    void handle_adding_plant(Event event, SpriteType adding_sprite, double, double);
    void render_cursor_following_sprite(RenderWindow &window);
    void add_plant(SpriteType sprite_type, double pos_x, double pos_y ,int row ,int col);
    int get_number_of_zombies();
};
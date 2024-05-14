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
    void update(State &state, double scale_x);
    void render(RenderWindow &window, Music &background_music);
    void add_zombie(SpriteType ,double ,double ,int);
    void add_bullet(BulletType ,int ,double ,double); 
    void delete_bullet(Bullet*) ;
    void generate_zombie();
    void handle_mouse_press(Event event, double, double);
    SpriteType get_random_zombie_type();
    void main_menu_render(RenderWindow &window);
    void game_over_render(RenderWindow &window);
    void victory_render(RenderWindow &window);
    void in_game_initialization();
    void handle_plants_shooting(); 
    void game_over_initialization();
    void handle_zombie_damages(double); 
    void clean_dead_plants(); 
    void check_moving_stopped_zombies(double); 
    void clean_sun() ; 
    void clean_outside_bullets();
    void clean_dead_zombies(); 
    void generate_random_sun(); 
    void check_peas_collision(); 
    void groan(); 
    bool is_in_same_field(Zombie* ,Plant* ,double); 
    ~Handler();
private:
    bool square_is_full[NUM_ROW][NUM_COLUMN] ,first_zombie_generate ;
    int zombie_amount_per_cycle ,giant_probability; 
    int zombie_cycle_time ,zombie_generate_duration ,zombie_increase_rate; 
    Clock clock ,last_zombie_increase_clock ,last_zombie_spawn_clock;
    vector <GameObject*> game_objects;
    vector <Sun*> suns;
    vector <Bullet*> bullets;
    vector <Zombie*> zombies_in_line[NUM_ROW]; 
    vector <Bullet*> bullets_in_line[NUM_ROW]; 
    Menu menu;
    Music first_zombie_coming ,zombie_groan[NUM_ZOMBIE_GROAN] ,collecting_suns ,splat[NUM_SPLATS];
    Music planting_sound ,huge_wave_sound ,siren_sound ,throw_music[NUM_THROW] ;
    Clock sun_generating_clock;
    Clock game_over_clock ,zombie_groan_clock;
    int number_of_suns ,groan_ptr ,splat_ptr ,throw_ptr ;
    Clock last_wave_message_clock;
    int sun_interval;
    bool have_small_zombie ,have_giant_zombie ; 
    void render_sun_bank(RenderWindow &window);
    void render_phase(RenderWindow &window);
    void render_last_wave_message(RenderWindow &window);
    void handle_adding_plant(Event event, SpriteType adding_sprite, double, double);
    void render_cursor_following_sprite(RenderWindow &window);
    void add_plant(SpriteType sprite_type, double pos_x, double pos_y ,int row ,int col);
    int get_number_of_zombies();
    Zombie* first_zombie_in_row(double x, int row_number);
    Zombie* last_Zombie_in_row(int); 
    void check_melons_collision();
    int phase;
    bool last_wave_message_display;
};
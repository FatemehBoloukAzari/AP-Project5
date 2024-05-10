#pragma once

#include "global_stuff.h"
#include "menu.h"
#include "zombie.h"
#include "sun.h"
#include "plant.h"

//#include "bullet.h"

enum State
{
    MAIN_MENU,
    IN_GAME,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    EXIT
};

class System
{
public:
    System(int width, int height);
    RenderWindow window;
    void update();
    void run();
    void handle_events();
    void render();
    void add_sprite(SpriteType ,int ,int);
    void generate_zombie();
    SpriteType get_random_zombie_type() ;
    //~System();
private:
    int zombie_amount_per_cycle ,giant_probability ; 
    Texture background;
    Sprite backgroundSprite;
    Clock clock ,last_zombie_increase_clock ,last_zombie_spawn_clock, game_over_clock;
    vector <GameObject*> game_objects;
    vector <Sun*> suns;
    //vector <Projectile*> projectiles;
    double scale_x;
    double scale_y;
    void render_sun_bank();
    Menu menu;
    State state;
    Clock sun_generating_clock;
    void handle_mouse_press(Event event);
    int number_of_suns;
    int sun_interval;
    void handle_adding_plant(Event event, SpriteType adding_sprite);
    void render_cursor_following_sprite(RenderWindow &window);
    void in_game_initialization();
    void game_over_initialization();
    void victory_initialization();
    void main_menu_render();
    void game_over_render();
    void victory_render();
    void add_plant(SpriteType sprite_type, double pos_x, double pos_y);
    Music music;
};
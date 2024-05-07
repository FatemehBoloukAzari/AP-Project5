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
    //~System();
private:
    Texture background;
    Sprite backgroundSprite;
    Clock clock, zombie_clock;
    //vector <Sprite*> sprites;
    vector <Sun*> suns;
    //vector <Bullet*> bullets;
    double scale_x;
    double scale_y;
    void render_sun_bank();
    Menu menu;
    State state;
    Clock sun_generating_clock;
    void handle_mouse_press(Event event);
    int number_of_suns;
    void handle_adding_plant(Event event, SpriteType adding_sprite);
    void render_cursor_following_sprite(RenderWindow &window);
};
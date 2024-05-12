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
#include "handler.h"

//#include "bullet.h"

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
    double scale_x;
    double scale_y;
    State state;
    void handle_mouse_press(Event event);
    void in_game_initialization();
    void game_over_initialization();
    void victory_initialization();
    void main_menu_render();
    void game_over_render();
    void victory_render();
    Music music;
    Handler *handler;
};
#pragma once

#include "global_stuff.h"
#include "menu.h"
#include "zombie.h"
#include "plant.h"

//#include "sun.h"
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
    void add_zombie(SpriteType);
    void generate_random_zombie(SpriteType); 
    //~System();
private:
    Texture background;
    Sprite backgroundSprite;
    Clock clock ,zombie_clock;
    /*vector <Sprite*> sprites;
    vector <Sun*> suns;
    vector <Bullet*> bullets;*/
    void render_sun_bank();
    Menu menu;
    State state;
    //void handle_mouse_press(Event ev);
};
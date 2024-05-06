#pragma once

#include "global_stuff.h"

class Sun
{
public:
    Sun(bool, int x_pos = 0, int y_pos = 0);
    void update();
    void render(RenderWindow &window);
    bool check_mouse_press(Event event);
    bool exited_screen();
private:
    int x;
    int y;
    bool is_moving;
    Texture sun_texture;
    Sprite sun_sprite;
    Clock last_move_clock;
    void move();
};
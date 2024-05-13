#pragma once

#include "global_stuff.h"

enum Direction {
    LEFT,
    RIGHT 
};

class Sun
{
public:
    Sun(bool, double x_pos = 0, double y_pos = 0);
    void update();
    void render(RenderWindow &window);
    bool check_mouse_press(Event event);
    bool exited_screen();
private:
    bool is_moving;
    double x ,delta_x;
    double y ,delta_y;
    int speed;
    Texture sun_texture;
    Sprite sun_sprite;
    Clock last_move_clock;
    Direction direction; 
    void move(double);
    void move_x(double); 
    void move_y();
};
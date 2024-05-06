#include "sun.h"

const int SUN_WIDTH = 100;
const int SUN_HEIGHT = 100;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Sun::Sun(bool moving, int x_pos, int y_pos)
{
    if (moving)
    {
        x_pos = rng() % (WIDTH - SUN_WIDTH);
        y_pos = 0;
    }
    x = x_pos;
    y = y_pos;
    is_moving = moving;
    sun_texture.loadFromFile(PICS_PATH + "sun.png");
    sun_sprite.setTexture(sun_texture);
}

void Sun::render(RenderWindow &window)
{
    double scale_x = (double)SUN_WIDTH / sun_texture.getSize().x;
    double scale_y = (double)SUN_HEIGHT / sun_texture.getSize().y;
    sun_sprite.setScale(scale_x, scale_y);
    sun_sprite.setPosition(x, y);
    window.draw(sun_sprite);
}

const int SUN_SPEED = 5;

void Sun::move()
{
    y += SUN_SPEED;
}
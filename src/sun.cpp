#include "sun.h"

const int SUN_WIDTH = 100;
const int SUN_HEIGHT = 100;

const int X_SPACE = 350;

const int ONE_SECOND = 1;

int SUN_SPEED = 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Sun::Sun(bool moving, int x_pos, int y_pos)
{
    if (moving)
    {
        x_pos = rng() % (WIDTH - SUN_WIDTH - X_SPACE) + X_SPACE;
        y_pos = 0;
    }
    x = x_pos;
    y = y_pos;
    is_moving = moving;
    sun_texture.loadFromFile(PICS_PATH + "sun.png");
    sun_sprite.setTexture(sun_texture);
    last_move_clock.restart();
}

void Sun::render(RenderWindow &window)
{
    double scale_x = (double)SUN_WIDTH / sun_texture.getSize().x;
    double scale_y = (double)SUN_HEIGHT / sun_texture.getSize().y;
    sun_sprite.setScale(scale_x, scale_y);
    sun_sprite.setPosition(x, y);
    window.draw(sun_sprite);
}

void Sun::move()
{
    y += SUN_SPEED;
}

bool Sun::check_mouse_press(Event event)
{
    Vector2f spritePos = sun_sprite.getPosition();
    Vector2f mousePos = {(float)event.mouseButton.x, (float)event.mouseButton.y};
    if (mousePos.x >= spritePos.x && mousePos.x <= spritePos.x + SUN_WIDTH &&
        mousePos.y >= spritePos.y && mousePos.y <= spritePos.y + SUN_HEIGHT)
    {
        return true;
    }
    return false;
}

void Sun::update()
{
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asSeconds() >= ONE_SECOND)
    {
        move();
        last_move_clock.restart();
    }
}
#include "sun.h"
#include "setting.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Sun::Sun(bool moving, double x_pos, double y_pos)
{
    if (moving)
    {
        x_pos = rng() % (WIDTH - SUN_WIDTH - X_SPACE) + X_SPACE;
        y_pos = 0;
        speed = read_sun_speed_from_file();
    }
    else
        speed = 0;
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

void Sun::move(double change_amount)
{
    y += change_amount;
}

bool Sun::check_mouse_press(Event event)
{
    Vector2f sprite_pos = sun_sprite.getPosition();
    Vector2f mouse_pos = {(float)event.mouseButton.x, (float)event.mouseButton.y};
    if (mouse_pos.x >= sprite_pos.x && mouse_pos.x <= sprite_pos.x + SUN_WIDTH &&
        mouse_pos.y >= sprite_pos.y && mouse_pos.y <= sprite_pos.y + SUN_HEIGHT)
    {
        return true;
    }
    return false;
}

bool Sun::exited_screen()
{
    if (y > HEIGHT)
        return true;
    return false;
}

void Sun::update()
{
    if (!is_moving)
        return;
    Time elapsed = last_move_clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= SUN_MOVE_INTERVAL)
    {
        move((double)speed / SCALE_MILLISECONDS);
        last_move_clock.restart();
    }
}
#pragma once

#include "global_stuff.h"

class MenuItem
{
public:
    MenuItem(SpriteType, int, int);
    void render(RenderWindow &window);
    void update();
private:
    int x;
    int y;
    Texture item_texture;
    Sprite item_sprite;
    int remaining_cooldown_time;
    SpriteType sprite_type;
};

class Menu
{
public:
    Menu();
    void update();
    void render(RenderWindow &window);
private:
    vector <MenuItem*> menu_items;
};
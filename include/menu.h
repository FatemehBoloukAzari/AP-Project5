#pragma once

#include "global_stuff.h"

enum SpriteType
{
    WALNUT,
    PEASHOOTER,
    SNOWPEA,
    MELONPULT,
    SUNFLOWER
};

class MenuItem
{
public:
    void render();
    void update();
private:
    int x;
    int y;
    Texture item_texture;
    int remaining_cooldown_time;
    SpriteType sprite_type;
};

class Menu
{
public:
    void update();
    void render();
private:
    vector <MenuItem*> menu_items;
};
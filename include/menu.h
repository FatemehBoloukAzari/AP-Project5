#pragma once

#include "global_stuff.h"

class MenuItem
{
public:
    MenuItem(SpriteType, int, int);
    void render(RenderWindow &window);
    void update();
    void handle_mouse_press(Event event, int number_of_suns);
    bool is_tagged();
    SpriteType get_sprite_type();
private:
    int x;
    int y;
    Texture item_texture;
    Sprite item_sprite;
    int remaining_cooldown_time;
    SpriteType sprite_type;
    bool on_cooldown;
    bool tagged;
    bool check_mouse_press(Event event);
};

class Menu
{
public:
    Menu();
    void update();
    void render(RenderWindow &window);
    void handle_mouse_press(Event event, int number_of_suns);
    SpriteType get_tagged_sprite();
private:
    vector <MenuItem*> menu_items;
};
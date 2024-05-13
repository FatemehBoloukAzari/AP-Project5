#pragma once

#include "global_stuff.h"

class MenuItem
{
public:
    MenuItem(SpriteType, int, int);
    void render(RenderWindow &window ,int number_of_suns);
    void update();
    void handle_mouse_press(Event event, int number_of_suns);
    bool is_tagged();
    void untag();
    void update_used_card();
    SpriteType get_sprite_type();
private:
    int x;
    int y;
    int cooldown;
    int price;
    Texture item_texture;
    Sprite item_sprite;
    Texture item_cooldown_texture;
    Sprite item_cooldown_sprite;
    SpriteType sprite_type;
    bool on_cooldown;
    bool tagged;
    Clock cooldown_clock;
    bool check_mouse_press(Event event);
    void normal_render(RenderWindow &window);
    void render_cooldown_card(RenderWindow &window, double);
    void cooldown_render(RenderWindow &window);
    void disabled_render(RenderWindow &window);
};

class Menu
{
public:
    Menu();
    void update();
    void render(RenderWindow &window ,int number_of_sun);
    void handle_mouse_press(Event event, int number_of_suns);
    SpriteType get_tagged_sprite();
    void update_used_card();
    void untag_tagged_item();
private:
    vector <MenuItem*> menu_items;
};
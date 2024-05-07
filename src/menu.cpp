#include "menu.h"
#include <iomanip>

const int CARD_WIDTH = 160;
const int CARD_HEIGHT = 100;

// move these to main (probably)
int WALNUT_CARD_COOLDOWN = 5;
int PEASHOOTER_CARD_COOLDOWN = 5;
int SNOWPEA_CARD_COOLDOWN = 5;
int MELONPULT_CARD_COOLDOWN = 5;
int SUNFLOWER_CARD_COOLDOWN = 5;

int WALNUT_PRICE = 5;
int PEASHOOTER_PRICE = 5;
int SNOWPEA_PRICE = 5;
int MELONPULT_PRICE = 5;
int SUNFLOWER_PRICE = 12;

MenuItem::MenuItem(SpriteType type, int x_pos, int y_pos)
{
    x = x_pos;
    y = y_pos;
    sprite_type = type;
    on_cooldown = false;
    tagged = false;
    switch (sprite_type)
    {
        case WALNUT:
            item_texture.loadFromFile(PICS_PATH + "menu_walnut.png");
            item_cooldown_texture.loadFromFile(PICS_PATH + "menu_walnut_cooldown.png");
            break;
        case PEASHOOTER:
            item_texture.loadFromFile(PICS_PATH + "menu_peashooter.png");
            item_cooldown_texture.loadFromFile(PICS_PATH + "menu_peashooter_cooldown.png");
            break;
        case SNOWPEA:
            item_texture.loadFromFile(PICS_PATH + "menu_snowpea.png");
            item_cooldown_texture.loadFromFile(PICS_PATH + "menu_snowpea_cooldown.png");
            break;
        case MELONPULT:
            item_texture.loadFromFile(PICS_PATH + "menu_melonpult.png");
            item_cooldown_texture.loadFromFile(PICS_PATH + "menu_melonpult_cooldown.png");
            break;
        case SUNFLOWER:
            item_texture.loadFromFile(PICS_PATH + "menu_sunflower.png");
            item_cooldown_texture.loadFromFile(PICS_PATH + "menu_sunflower_cooldown.png");
            break;
        default:
            break;
    }
    item_sprite.setTexture(item_texture);
    item_cooldown_sprite.setTexture(item_cooldown_texture);
}

void MenuItem::normal_render(RenderWindow &window)
{
    double scale_x = (double)CARD_WIDTH / item_texture.getSize().x;
    double scale_y = (double)CARD_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setPosition(x, y);
    window.draw(item_sprite);
    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "randomfont.ttf");
    Text text;
    switch (sprite_type)
    {
        case WALNUT:
            text.setString(to_string(WALNUT_PRICE));
            break;
        case PEASHOOTER:
            text.setString(to_string(PEASHOOTER_PRICE));
            break;
        case SNOWPEA:
            text.setString(to_string(SNOWPEA_PRICE));
            break;
        case MELONPULT:
            text.setString(to_string(MELONPULT_PRICE));
            break;
        case SUNFLOWER:
            text.setString(to_string(SUNFLOWER_PRICE));
            break;
        default:
            break;
    }
    text.setFillColor(Color::White);
    text.setFont(new_font);
    text.setCharacterSize(35);
    text.setPosition(x + 123, y + 50);
    text.setStyle(Text::Bold);
    window.draw(text);
}

int get_cooldown_time(SpriteType sprite_type)
{
    switch (sprite_type)
    {
        case WALNUT:
            return WALNUT_CARD_COOLDOWN;
        case PEASHOOTER:
            return PEASHOOTER_CARD_COOLDOWN;
        case SNOWPEA:
            return SNOWPEA_CARD_COOLDOWN;
        case MELONPULT:
            return MELONPULT_CARD_COOLDOWN;
        case SUNFLOWER:
            return SUNFLOWER_CARD_COOLDOWN;
        default:
            break;
    }
    return 0;
}

void MenuItem::cooldown_render(RenderWindow &window)
{
    double scale_x = (double)CARD_WIDTH / item_texture.getSize().x;
    double scale_y = (double)CARD_HEIGHT / item_texture.getSize().y;
    item_cooldown_sprite.setScale(scale_x, scale_y);
    item_cooldown_sprite.setPosition(x, y);
    window.draw(item_cooldown_sprite);
    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "randomfont.ttf");
    Text text;
    Time elapsed = cooldown_clock.getElapsedTime();
    double remaning_cooldown_time = get_cooldown_time(sprite_type) - elapsed.asSeconds();
    ostringstream stream;
    stream << fixed << setprecision(1) << remaning_cooldown_time;
    text.setString(stream.str());
    text.setFillColor(Color::Red);
    text.setFont(new_font);
    text.setCharacterSize(35);
    text.setPosition(x + 60, y + 25);
    text.setStyle(Text::Bold);
    window.draw(text);
    switch (sprite_type)
    {
        case WALNUT:
            text.setString(to_string(WALNUT_PRICE));
            break;
        case PEASHOOTER:
            text.setString(to_string(PEASHOOTER_PRICE));
            break;
        case SNOWPEA:
            text.setString(to_string(SNOWPEA_PRICE));
            break;
        case MELONPULT:
            text.setString(to_string(MELONPULT_PRICE));
            break;
        case SUNFLOWER:
            text.setString(to_string(SUNFLOWER_PRICE));
            break;
        default:
            break;
    }
    text.setFillColor(Color::White);
    text.setFont(new_font);
    text.setCharacterSize(35);
    text.setPosition(x + 123, y + 50);
    text.setStyle(Text::Bold);
    window.draw(text);
}

void MenuItem::render(RenderWindow &window)
{
    if (!on_cooldown)
        normal_render(window);
    else
        cooldown_render(window);
}

void Menu::render(RenderWindow &window)
{
    for (auto &item : menu_items)
        item->render(window);
}

Menu::Menu()
{
    int y_pos = 100;
    int x_pos = 20;
    int space_y = 3;
    for (int type = WALNUT; type != NOT_SPRITE; type++)
    {
        SpriteType sprite_type = static_cast<SpriteType>(type);
        MenuItem* new_menu_item = new MenuItem(sprite_type, x_pos, y_pos);
        menu_items.push_back(new_menu_item);
        y_pos += CARD_HEIGHT + space_y;
    }
}

bool MenuItem::check_mouse_press(Event event)
{
    Vector2f sprite_pos = item_sprite.getPosition();
    Vector2f mouse_pos = {(float)event.mouseButton.x, (float)event.mouseButton.y};
    if (mouse_pos.x >= sprite_pos.x && mouse_pos.x <= sprite_pos.x + CARD_WIDTH &&
        mouse_pos.y >= sprite_pos.y && mouse_pos.y <= sprite_pos.y + CARD_HEIGHT)
    {
        return true;
    }
    return false;
}

void MenuItem::handle_mouse_press(Event event, int number_of_suns)
{
    if (!check_mouse_press(event) || on_cooldown || tagged)
        return;
    int price = 0;
    switch (sprite_type)
    {
        case WALNUT:
            price = WALNUT_PRICE;
            break;
        case PEASHOOTER:
            price = PEASHOOTER_PRICE;
            break;
        case SNOWPEA:
            price = SNOWPEA_PRICE;
            break;
        case MELONPULT:
            price = MELONPULT_PRICE;
            break;
        case SUNFLOWER:
            price = SUNFLOWER_PRICE;
            break;
        default:
            break;
    }
    if (price > number_of_suns)
        return;
    tagged = true;
}

void Menu::handle_mouse_press(Event event, int number_of_suns)
{
    for (auto &menu_item : menu_items)
        menu_item->handle_mouse_press(event, number_of_suns);
}

bool MenuItem::is_tagged()
{
    return tagged;
}

SpriteType MenuItem::get_sprite_type()
{
    return sprite_type;
}

SpriteType Menu::get_tagged_sprite()
{
    for (auto &menu_item : menu_items)
        if (menu_item->is_tagged())
            return menu_item->get_sprite_type();
    return NOT_SPRITE;
}

void MenuItem::update_used_card()
{
    cooldown_clock.restart();
    on_cooldown = true;
}

void Menu::update_used_card()
{
    for (auto &menu_item : menu_items)
        if (menu_item->is_tagged())
            menu_item->update_used_card();
}

void MenuItem::untag()
{
    tagged = false;
}

void Menu::untag_tagged_item()
{
    for (auto &menu_item : menu_items)
        if (menu_item->is_tagged())
            menu_item->untag();
}

void MenuItem::update()
{
    Time elapsed = cooldown_clock.getElapsedTime();
    if (elapsed.asSeconds() >= get_cooldown_time(sprite_type))
        on_cooldown = false;
}

void Menu::update()
{
    for (auto &menu_item : menu_items)
        menu_item->update();
}
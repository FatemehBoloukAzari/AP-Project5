#include "menu.h"

const int CARD_WIDTH = 200;
const int CARD_HEIGHT = 120;

MenuItem::MenuItem(SpriteType type, int x_pos, int y_pos)
{
    x = x_pos;
    y = y_pos;
    switch (type)
    {
        case WALNUT:
            item_texture.loadFromFile(PICS_PATH + "menu_walnut.png");
            remaining_cooldown_time = WALNUT_CARD_COOLDOWN;
            break;
        case PEASHOOTER:
            item_texture.loadFromFile(PICS_PATH + "menu_peashooter.png");
            remaining_cooldown_time = PEASHOOTER_CARD_COOLDOWN;
            break;
        case SNOWPEA:
            item_texture.loadFromFile(PICS_PATH + "menu_snowpea.png");
            remaining_cooldown_time = SNOWPEA_CARD_COOLDOWN;
            break;
        case MELONPULT:
            item_texture.loadFromFile(PICS_PATH + "menu_melonpult.png");
            remaining_cooldown_time = MELONPULT_CARD_COOLDOWN;
            break;
        case SUNFLOWER:
            item_texture.loadFromFile(PICS_PATH + "menu_sunflower.png");
            remaining_cooldown_time = SUNFLOWER_CARD_COOLDOWN;
            break;
        default:
            break;
    }
    item_sprite.setTexture(item_texture);
}

void MenuItem::render(RenderWindow &window)
{
    double scale_x = (double)CARD_WIDTH / item_texture.getSize().x;
    double scale_y = (double)CARD_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setPosition(x, y);
    window.draw(item_sprite);
    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "randomfont.ttf");
    Text text;
    int number_of_suns = 13;//suns.size();
    text.setString(to_string(number_of_suns));
    text.setFillColor(Color::Black);
    text.setFont(new_font);
    text.setCharacterSize(40);
    text.setPosition(x + 150, y + 60);
    text.setStyle(Text::Bold);
    window.draw(text);
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
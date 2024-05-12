#include "menu.h"
#include "setting.h"
#include <iomanip>

MenuItem::MenuItem(SpriteType type, int x_pos, int y_pos)
{
    x = x_pos;
    y = y_pos;
    sprite_type = type;
    on_cooldown = false;
    tagged = false;
    cooldown = read_plant_cooldown_from_file(sprite_type);
    price = read_plant_price_from_file(sprite_type);
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
    new_font.loadFromFile(FONTS_PATH + "HouseOfTerrorRegular.otf");
    Text text;
    text.setString(to_string(price));
    text.setFillColor(Color::White);
    text.setFont(new_font);
    text.setCharacterSize(35);
    text.setPosition(x + 123, y + 50);
    text.setStyle(Text::Bold);
    window.draw(text);
}

Color to_gray_scale(const sf::Color& color)
{
    unsigned char gray = color.r * 0.2126f + color.g * 0.7152f + color.b * 0.0722f;
    return Color(gray, gray, gray, color.a);
}

void MenuItem::render_cooldown_card(RenderWindow &window, double remaning_cooldown_time)
{
    item_cooldown_sprite.setTexture(item_cooldown_texture);
    Image image = item_cooldown_texture.copyToImage();
    Vector2u image_size = image.getSize();
    int number_of_gray_rows = remaning_cooldown_time / cooldown * image_size.y;

    for (int y = 0; y < number_of_gray_rows; y++)
    {
        for (int x = 0; x < (int)image_size.x; x++)
        {
            Color pixelColor = image.getPixel(x, y);
            pixelColor = to_gray_scale(pixelColor);
            image.setPixel(x, y, pixelColor);
        }
    }
    Texture in_cooldown_texture;
    in_cooldown_texture.loadFromImage(image);
    item_cooldown_sprite.setTexture(in_cooldown_texture);
    window.draw(item_cooldown_sprite);
}

void MenuItem::cooldown_render(RenderWindow &window)
{
    double scale_x = (double)CARD_WIDTH / item_texture.getSize().x;
    double scale_y = (double)CARD_HEIGHT / item_texture.getSize().y;
    item_cooldown_sprite.setScale(scale_x, scale_y);
    item_cooldown_sprite.setPosition(x, y);
    //window.draw(item_cooldown_sprite);
    Time elapsed = cooldown_clock.getElapsedTime();
    double remaning_cooldown_time = cooldown - elapsed.asSeconds();
    render_cooldown_card(window, remaning_cooldown_time);
    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "HouseOfTerrorRegular.otf");
    Text text;
    ostringstream stream;
    stream << fixed << setprecision(1) << remaning_cooldown_time;
    text.setString(stream.str());
    text.setFillColor(Color::Red);
    text.setFont(new_font);
    text.setCharacterSize(35);
    text.setPosition(x + 60, y + 25);
    text.setStyle(Text::Bold);
    window.draw(text);
    text.setString(to_string(price));
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
    if (elapsed.asSeconds() >= cooldown)
        on_cooldown = false;
}

void Menu::update()
{
    for (auto &menu_item : menu_items)
        menu_item->update();
}
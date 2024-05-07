#include "system.h"

const int SUN_BANK_WIDTH = 250;
const int SUN_BANK_HEIGHT = 75;

const int INITIAL_NUMBER_OF_SUNS = 10;

const bool MOVING_SUN = true;
const bool NOT_MOVING_SUN = false;

const pair <int, int> NO_SQUARE = {-1, -1};

int SUN_INTERVAL = 5;

System::System(int width, int height)
{
    window.create(VideoMode(width, height), "PVZ", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    if (!background.loadFromFile(PICS_PATH + "background.png"))
        cout << "failed to open" << endl;
    backgroundSprite.setTexture(background);
    scale_x = (float)window.getSize().x / background.getSize().x;
    scale_y = (float)window.getSize().y / background.getSize().y;
    backgroundSprite.setScale(scale_x, scale_y);
    state = IN_GAME;
    sun_generating_clock.restart();
    number_of_suns = INITIAL_NUMBER_OF_SUNS;
}

void System::render_sun_bank()
{
    Texture sun_bank_texture;
    sun_bank_texture.loadFromFile(PICS_PATH + "sun_bank.png");
    Sprite sun_bank_sprite;
    sun_bank_sprite.setTexture(sun_bank_texture);
    double scale_x = (double)SUN_BANK_WIDTH / sun_bank_texture.getSize().x;
    double scale_y = (double)SUN_BANK_HEIGHT / sun_bank_texture.getSize().y;
    sun_bank_sprite.setScale(scale_x, scale_y);
    sun_bank_sprite.setPosition(20, 5);
    window.draw(sun_bank_sprite);
    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "randomfont.ttf");
    Text text;
    text.setString(to_string(number_of_suns));
    text.setFillColor(Color::Black);
    text.setFont(new_font);
    text.setCharacterSize(50);
    text.setPosition(150, 13);
    text.setStyle(Text::Bold);
    window.draw(text);
}

void System::render()
{
    window.clear();
    window.draw(backgroundSprite);
    render_sun_bank();
    for (auto &sun : suns)
        sun->render(window);
    menu.render(window);
    window.display();
}


void System::update()
{
    Time elapsed = sun_generating_clock.getElapsedTime();
    if (elapsed.asSeconds() >= SUN_INTERVAL)
    {
        sun_generating_clock.restart();
        Sun *new_sun = new Sun(MOVING_SUN);
        suns.push_back(new_sun);
    }
    for (auto it = suns.begin(); it != suns.end();)
    {
        (*it)->update();
        if ((*it)->exited_screen())
        {
            Sun* exited_sun = *it;
            it = suns.erase(it);
            delete exited_sun;
        }
        else
            it++;
    }
}

double get_scaled_x(double val, double scale_x)
{
    return val * scale_x;
}

double get_scaled_y(double val, double scale_y)
{
    return val * scale_y;
}

pair <int, int> get_clicked_square(Event event, double scale_x, double scale_y)
{
    Vector2f mouse_pos = {(float)event.mouseButton.x, (float)event.mouseButton.y};
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            double x1 = get_scaled_x(field_square_x[j], scale_x), x2 = get_scaled_x(field_square_x[j + 1], scale_x);
            double y1 = get_scaled_y(field_square_y[i], scale_y), y2 = get_scaled_y(field_square_y[i + 1], scale_y);
            if (y1 <= mouse_pos.y && mouse_pos.y <= y2 && 
                x1 <= mouse_pos.x && mouse_pos.x <= x2)
                return {i, j};
        }
    }
    return NO_SQUARE;
}

int get_price(SpriteType sprite_type)
{
    switch (sprite_type)
    {
        case WALNUT:
            return WALNUT_PRICE;
        case PEASHOOTER:
            return PEASHOOTER_PRICE;
        case SNOWPEA:
            return SNOWPEA_PRICE;
        case MELONPULT:
            return MELONPULT_PRICE;
        case SUNFLOWER:
            return SUNFLOWER_PRICE;
        default:
            break;
    }
    return 0;
}

void System::handle_adding_plant(Event event, SpriteType adding_sprite)
{
    pair <int, int> clicked_square = get_clicked_square(event, scale_x, scale_y);
    if (clicked_square == NO_SQUARE)
        return;
    int price = get_price(adding_sprite);
    number_of_suns -= price;
    // oon sprite ro untage konim va start bezanim cooldownesh ro va ghiafasho avaz konim va in harfa
    // untage bayad hata age clicked squar no square bood ham anjam she
    //add_plant(adding_sprite, right position to add)
}

void System::handle_mouse_press(Event event)
{
    for (auto it = suns.begin(); it != suns.end();)
    {
        if ((*it)->check_mouse_press(event))
        {
            Sun* pressed_sun = *it;
            number_of_suns++;
            it = suns.erase(it);
            delete pressed_sun;
        }
        else
            it++;
    }
    menu.handle_mouse_press(event, number_of_suns);
    SpriteType adding_sprite = menu.get_tagged_sprite();
    if (adding_sprite != NOT_SPRITE)
        handle_adding_plant(event, adding_sprite);
}

void System::handle_events()
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case (Event::Closed):
                window.close();
                state = EXIT;
                break;
            case (Event::MouseButtonPressed):
                handle_mouse_press(event);
                break;
            default:
                break;
        }
    }
}

void System::run()
{
    while (window.isOpen() && state != EXIT)
    {
        handle_events();
        update();
        render();
    }
}
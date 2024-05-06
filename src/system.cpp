#include "system.h"

const int SUN_BANK_WIDTH = 250;
const int SUN_BANK_HEIGHT = 75;

const bool MOVING_SUN = true;
const bool NOT_MOVING_SUN = false;

int SUN_INTERVAL = 5;

System::System(int width, int height)
{
    window.create(VideoMode(width, height), "PVZ", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    if (!background.loadFromFile(PICS_PATH + "background.png"))
        cout << "failed to open" << endl;
    backgroundSprite.setTexture(background);
    float scale_x = (float)window.getSize().x / background.getSize().x;
    float scale_y = (float)window.getSize().y / background.getSize().y;
    backgroundSprite.setScale(scale_x, scale_y);
    state = IN_GAME;
    sun_generating_clock.restart();
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
    int number_of_suns = 5;//suns.size();
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
    for (auto &sun : suns)
        sun->update();
}

void System::run()
{
    while (window.isOpen() && state != EXIT)
    {
        //handle_events();
        update();
        render();
    }
}
#include "system.h"

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
}

void System::render()
{
    window.clear();
    window.draw(backgroundSprite);
    Texture sun_bank_texture;
    sun_bank_texture.loadFromFile(PICS_PATH + "sun_bank.png");
    Sprite sun_bank_sprite;
    sun_bank_sprite.setTexture(sun_bank_texture);
    sun_bank_sprite.setPosition(20, 5);
    window.draw(sun_bank_sprite);
    menu.render(window);
    window.display();
}

void System::run()
{
    while (window.isOpen() && state != EXIT)
    {
        //handle_events();
        //update();
        render();
    }
}
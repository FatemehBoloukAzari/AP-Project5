#include "system.h"
#include "setting.h"

System::System(int width, int height)
{
    window.create(VideoMode(width, height), "PVZ", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    if (!background.loadFromFile(PICS_PATH + "main_menu.png"))
        cerr << "failed to open" << endl;
    backgroundSprite.setTexture(background);
    scale_x = (float)window.getSize().x / background.getSize().x;
    scale_y = (float)window.getSize().y / background.getSize().y;
    backgroundSprite.setScale(scale_x, scale_y);
    music.openFromFile(AUDIO_PATH + "main_menu.wav");
    music.setLoop(true);
    music.play();
    state = MAIN_MENU;
    handler = new Handler();
}

void System::in_game_initialization()
{
    if (!background.loadFromFile(PICS_PATH + "background.png"))
        cerr << "failed to open" << endl;
    backgroundSprite.setTexture(background, true);
    scale_x = (float)window.getSize().x / backgroundSprite.getLocalBounds().width;
    scale_y = (float)window.getSize().y / backgroundSprite.getLocalBounds().height;
    backgroundSprite.setScale(scale_x, scale_y);
    handler->in_game_initialization();
    music.openFromFile(AUDIO_PATH + "in_game.wav");
    music.setLoop(true);
    music.play();
}

void System::game_over_initialization()
{
    if (!background.loadFromFile(PICS_PATH + "background.png"))
        cerr << "failed to open" << endl;
    backgroundSprite.setTexture(background, true);
    scale_x = (float)window.getSize().x / backgroundSprite.getLocalBounds().width;
    scale_y = (float)window.getSize().y / backgroundSprite.getLocalBounds().height;
    backgroundSprite.setScale(scale_x, scale_y);
    music.openFromFile(AUDIO_PATH + "game_over.wav");
    music.setLoop(false);
    music.play();
    game_over_clock.restart();
}

void System::victory_initialization()
{
    if (!background.loadFromFile(PICS_PATH + "victory_screen.png"))
        cerr << "failed to open" << endl;
    backgroundSprite.setTexture(background, true);
    scale_x = (float)window.getSize().x / backgroundSprite.getLocalBounds().width;
    scale_y = (float)window.getSize().y / backgroundSprite.getLocalBounds().height;
    backgroundSprite.setScale(scale_x, scale_y);
    music.openFromFile(AUDIO_PATH + "victory.wav");
    music.setLoop(false);
    music.play();
}

void System::render()
{
    window.clear();
    window.draw(backgroundSprite);
    handler->render(window);
    //cout << game_objects.size() << endl ; 
    window.display();
}

void System::victory_render()
{
    window.clear();
    window.draw(backgroundSprite);
    window.display();
}

void System::update()
{
    handler->update();
}

void System::handle_mouse_press(Event event)
{
    handler->handle_mouse_press(event, scale_x, scale_y);
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
            case (Event::KeyPressed):
                if (state == MAIN_MENU)
                    state = IN_GAME;
                break;
            default:
                break;
        }
    }
}

void System::game_over_render()
{
    window.clear();
    window.draw(backgroundSprite);
    handler->game_over_render(window);
    RectangleShape rect;
    rect.setFillColor(Color(0, 0, 0, 200));
    rect.setSize(Vector2f(window.getSize().x, window.getSize().y));
    window.draw(rect);

    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "Creepster-Regular.ttf");
    Text text;
    text.setFillColor(Color::Green);
    text.setFont(new_font);
    text.setCharacterSize(150);

    text.setString("THE ZOMBIES");
    int x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    int y_pos = (HEIGHT - text.getLocalBounds().height) / 2;
    text.setPosition(x_pos, y_pos - 180);
    if (game_over_clock.getElapsedTime().asSeconds() > 3)
        window.draw(text);
    text.setString("ATE YOUR");
    x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    text.setPosition(x_pos, y_pos);
    if (game_over_clock.getElapsedTime().asSeconds() > 5)
        window.draw(text);
    text.setString("BRAINS!");
    text.setCharacterSize(220);
    x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    text.setPosition(x_pos, y_pos + 180);
    if (game_over_clock.getElapsedTime().asSeconds() > 6)
        window.draw(text);
    window.display();
}

void System::main_menu_render()
{
    window.clear();
    window.draw(backgroundSprite);
    handler->main_menu_render(window);
    window.display();
}

void System::run()
{
    while (window.isOpen() && state == MAIN_MENU)
    {
        main_menu_render();
        handle_events();
    }
    in_game_initialization();
    int x = 0;
    while (window.isOpen() && state == IN_GAME)
    {
        handler->generate_zombie() ;
        handle_events();
        update();
        render();
        x++;
        if (x == 200)
            state = GAMEOVER_SCREEN;
    }
    victory_initialization();
    while (window.isOpen() && state == VICTORY_SCREEN)
    {
        handle_events();
        victory_render();
    }
    game_over_initialization();
    while (window.isOpen() && state == GAMEOVER_SCREEN)
    {
        handle_events();
        game_over_render();
    }
}

/*System::~System()
{
    music.~Music();
    delete handler;
}*/
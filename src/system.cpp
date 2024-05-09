#include "system.h"
#include "setting.h"

const int SUN_BANK_WIDTH = 250;
const int SUN_BANK_HEIGHT = 75;

const int REGULAR_WIDTH = 110;
const int REGULAR_HEIGHT = 180; 
const int HAIRMETALGARGANTUAR_WIDTH = 240; 
const int HAIRMETALGARGANTUAR_HEIGHT = 250; 

const int INITIAL_NUMBER_OF_SUNS = 10;

const bool MOVING_SUN = true;
const bool NOT_MOVING_SUN = false;

const int MOVING_SPRITE_WIDTH = 100;
const int MOVING_SPRITE_HEIGHT = 100;

const pair <int, int> NO_SQUARE = {-1, -1};

bool square_is_full[ROW][COLUMN];

int ZOMBIE_GENERATE_DURATION = 100 ; 
int ZOMBIE_CYCLE_TIME = 10 ; 
int ZOMBIE_CYCLE_START_AMOUNT = 5; 
int ZOMBIE_INCREASE_RATE = 1 ;

System::System(int width, int height)
{
    window.create(VideoMode(width, height), "PVZ", Style::Close);
    window.setFramerateLimit(FRAME_RATE);
    if (!background.loadFromFile(PICS_PATH + "main_menu.png"))
        cout << "failed to open" << endl;
    backgroundSprite.setTexture(background);
    scale_x = (float)window.getSize().x / background.getSize().x;
    scale_y = (float)window.getSize().y / background.getSize().y;
    backgroundSprite.setScale(scale_x, scale_y);
    sun_interval = read_sun_interval_from_file();
    state = MAIN_MENU;
    zombie_amount_per_cycle = ZOMBIE_CYCLE_START_AMOUNT ; 
    giant_probability = -18 ; 
}

void System::in_game_initialization()
{
    if (!background.loadFromFile(PICS_PATH + "background.png"))
        cout << "failed to open" << endl;
    backgroundSprite.setTexture(background, true);
    scale_x = (float)window.getSize().x / backgroundSprite.getLocalBounds().width;
    scale_y = (float)window.getSize().y / backgroundSprite.getLocalBounds().height;
    backgroundSprite.setScale(scale_x, scale_y);
    sun_generating_clock.restart();
    number_of_suns = INITIAL_NUMBER_OF_SUNS;
    music.openFromFile(AUDIO_PATH + "in_game.wav");
    music.setLoop(true);
    music.play();
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
    new_font.loadFromFile(FONTS_PATH + "HouseOfTerrorRegular.otf");
    Text text;
    text.setString(to_string(number_of_suns));
    text.setFillColor(Color::Black);
    text.setFont(new_font);
    text.setCharacterSize(50);
    text.setPosition(150, 13);
    text.setStyle(Text::Bold);
    window.draw(text);
}

void System::render_cursor_following_sprite(RenderWindow &window)
{
    if (menu.get_tagged_sprite() == NOT_SPRITE)
        return;
    Texture item_texture;
    switch (menu.get_tagged_sprite())
    {
        case WALNUT:
            item_texture.loadFromFile(PICS_PATH + "defai.png");
            break;
        case PEASHOOTER:
            item_texture.loadFromFile(PICS_PATH + "nokhode_shooti.png");
            break;
        case SNOWPEA:
            item_texture.loadFromFile(PICS_PATH + "nokhode_barfi.png");
            break;
        case MELONPULT:
            item_texture.loadFromFile(PICS_PATH + "hendevane_part_kon.png");
            break;
        case SUNFLOWER:
            item_texture.loadFromFile(PICS_PATH + "aftab_gardoon.png");           
            break;
        default:
            break;
    }
    Sprite item_sprite;
    item_sprite.setTexture(item_texture);
    // instead of MOVING_SPRITE_WIDTH and MOVING_SPRITE_HEIGHT we can use the specified size
    // for each sprite (the size that is used for adding the sprite to the field)
    double scale_x = (double)MOVING_SPRITE_WIDTH / item_texture.getSize().x;
    double scale_y = (double)MOVING_SPRITE_HEIGHT / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setOrigin(item_sprite.getLocalBounds().width / 2, item_sprite.getLocalBounds().height / 2);
    Vector2i mouse_position = Mouse::getPosition(window);
    item_sprite.setPosition(static_cast<Vector2f>(mouse_position));
    window.draw(item_sprite);
}

void System::render()
{
    window.clear();
    window.draw(backgroundSprite);
    render_sun_bank();
    for (auto &game_object : game_objects)
        game_object->render(window) ; 
    for (auto &sun : suns)
        sun->render(window);
    cout << game_objects.size() << endl ; 
    menu.render(window);
    render_cursor_following_sprite(window);
    window.display();
}

void System::main_menu_render()
{
    window.clear();
    window.draw(backgroundSprite);
    Font new_font;
    new_font.loadFromFile(FONTS_PATH + "HouseOfTerrorRegular.otf");
    Text text;
    text.setString("Press any key to start");
    text.setFillColor(Color::Black);
    text.setFont(new_font);
    text.setCharacterSize(150);
    int x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    int y_pos = (HEIGHT - text.getLocalBounds().height) / 2;
    text.setPosition(x_pos, y_pos);
    text.setStyle(Text::Bold);
    Text shadow = text;
    shadow.setFillColor(Color(0, 0, 0, 128));
    shadow.move(6, -6);
    window.draw(shadow);
    window.draw(text);
    window.display();
}

void System::update()
{
    Time elapsed = sun_generating_clock.getElapsedTime();
    if (elapsed.asSeconds() >= sun_interval)
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
    menu.update();
    for (auto &game_object : game_objects)
        game_object->update() ; 
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

void System::handle_adding_plant(Event event, SpriteType adding_sprite)
{
    pair <int, int> clicked_square = get_clicked_square(event, scale_x, scale_y);
    if (clicked_square == NO_SQUARE || square_is_full[clicked_square.first][clicked_square.second])
    {
        menu.untag_tagged_item();
        return;
    }
    int price = read_plant_price_from_file(adding_sprite);
    number_of_suns -= price;
    menu.update_used_card();
    menu.untag_tagged_item();
    square_is_full[clicked_square.first][clicked_square.second] = true;
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
    SpriteType adding_sprite = menu.get_tagged_sprite();
    if (adding_sprite != NOT_SPRITE)
        handle_adding_plant(event, adding_sprite);
    menu.handle_mouse_press(event, number_of_suns);
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
    render_sun_bank();
    for (auto &sun : suns)
        sun->render(window);
    menu.render(window);
    render_cursor_following_sprite(window);
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
    window.draw(text);
    text.setString("ATE YOUR");
    x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    text.setPosition(x_pos, y_pos);
    window.draw(text);
    text.setString("BRAINS!");
    x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    text.setPosition(x_pos, y_pos + 180);
    window.draw(text);
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
    while (window.isOpen() && state == IN_GAME)
    {
        generate_zombie() ; 
        handle_events();
        update();
        render();
    }
    /*while (window.isOpen() && state == VICTORY_SCREEN)
    {
        handle_events();
        update();
        render();
    }*/
    while (window.isOpen() && state == GAMEOVER_SCREEN)
    {
        game_over_render();
    }
}

void System::add_sprite(SpriteType sprite_type ,int x ,int y){
    Zombie* zombie ; 
    switch (sprite_type){
    case REGULAR :
        zombie = new Zombie(x ,y ,sprite_type) ; 
        game_objects.push_back(zombie) ;   
        break;
    case HAIRMETALGARGANTUAR: 
        zombie = new Zombie(x ,y ,sprite_type) ; 
        game_objects.push_back(zombie) ;
        break; 
    default:
        break;
    }
}

SpriteType System::get_random_zombie_type(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    if (giant_probability <= 0) 
        return REGULAR ; 
    int rand_num = rng() % 150 ;
    if (rand_num + 1 <= giant_probability)
       return HAIRMETALGARGANTUAR ;  
    return REGULAR ;
}

void System::generate_zombie(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= ZOMBIE_GENERATE_DURATION) 
        return ;
    if (zombie_amount_per_cycle > 0){
        float needed_time_to_release_new_zombie = ZOMBIE_CYCLE_TIME / zombie_amount_per_cycle ; 
        cout << needed_time_to_release_new_zombie << endl ;
        elapsed = last_zombie_spawn_clock.getElapsedTime() ; 
        if (elapsed.asSeconds() >= needed_time_to_release_new_zombie){
            SpriteType sprite_type = get_random_zombie_type() ; 
            int y = row_spawn_height_giant[rng() % NUM_ROW] ;
            if (sprite_type == REGULAR)
                y = row_spawn_height_regular[rng() % NUM_ROW] ; 
            add_sprite(sprite_type ,WIDTH - (sprite_type == REGULAR ? REGULAR_WIDTH : HAIRMETALGARGANTUAR_WIDTH),y) ; 
            last_zombie_spawn_clock.restart() ; 
            giant_probability++ ; 
        }
    }
    elapsed = last_zombie_increase_clock.getElapsedTime() ; 
    if (elapsed.asSeconds() >= ZOMBIE_CYCLE_TIME){
        last_zombie_increase_clock.restart() ; 
        zombie_amount_per_cycle += ZOMBIE_INCREASE_RATE ;
    }
}


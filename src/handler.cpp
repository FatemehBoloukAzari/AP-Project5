#include "handler.h"
#include "setting.h"

Handler::Handler()
{
    memset(square_is_full ,false ,sizeof square_is_full);
    zombie_amount_per_cycle = read_first_interval_zombies() ;
    zombie_cycle_time = read_attack_interval() ; 
    zombie_generate_duration = read_total_attack_time() ; 
    zombie_increase_rate = read_zombie_number_change() ; 
    giant_probability = -18 ;
    sun_interval = read_sun_interval_from_file();
    number_of_suns = INITIAL_NUMBER_OF_SUNS;
}

void Handler::render_sun_bank(RenderWindow &window)
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

void Handler::render_cursor_following_sprite(RenderWindow &window)
{
    if (menu.get_tagged_sprite() == NOT_SPRITE)
        return;
    Texture item_texture;
    int moving_sprite_width;
    int moving_sprite_height;
    switch (menu.get_tagged_sprite())
    {
        case WALNUT:
            item_texture.loadFromFile(PICS_PATH + "defai.png");
            moving_sprite_width = WALNUT_WIDTH;
            moving_sprite_height = WALNUT_HEIGHT;
            break;
        case PEASHOOTER:
            item_texture.loadFromFile(PICS_PATH + "nokhode_shooti.png");
            moving_sprite_width = PEASHOOTER_WIDTH;
            moving_sprite_height = PEASHOOTER_HEIGHT;
            break;
        case SNOWPEA:
            item_texture.loadFromFile(PICS_PATH + "nokhode_barfi.png");
            moving_sprite_width = SNOWPEA_WIDTH;
            moving_sprite_height = SNOWPEA_HEIGHT;
            break;
        case MELONPULT:
            item_texture.loadFromFile(PICS_PATH + "hendevane_part_kon.png");
            moving_sprite_width = MELONPULT_WIDTH;
            moving_sprite_height = MELONPULT_HEIGHT;
            break;
        case SUNFLOWER:
            item_texture.loadFromFile(PICS_PATH + "aftab_gardoon.png");
            moving_sprite_width = SUNFLOWER_WIDTH;
            moving_sprite_height = SUNFLOWER_HEIGHT;
            break;
        default:
            break;
    }
    Sprite item_sprite;
    item_sprite.setTexture(item_texture);
    double scale_x = (double)moving_sprite_width / item_texture.getSize().x;
    double scale_y = (double)moving_sprite_height / item_texture.getSize().y;
    item_sprite.setScale(scale_x, scale_y);
    item_sprite.setOrigin(item_sprite.getLocalBounds().width / 2, item_sprite.getLocalBounds().height / 2);
    Vector2i mouse_position = Mouse::getPosition(window);
    item_sprite.setPosition(static_cast<Vector2f>(mouse_position));
    window.draw(item_sprite);
}

void Handler::main_menu_render(RenderWindow &window)
{
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
    for (int i = 0; i < NUM_ROW; i++)
    {
        for (int j = 0; j < NUM_COLUMN; j++)
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

void Handler::add_plant(SpriteType sprite_type, double pos_x, double pos_y)
{
    Plant* new_plant = new Plant(pos_x, pos_y, sprite_type);
    game_objects.push_back(new_plant);
}

void Handler::handle_adding_plant(Event event, SpriteType adding_sprite, double scale_x, double scale_y)
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
    int row = clicked_square.first, col = clicked_square.second;
    double x_pos = (field_square_x[col] + field_square_x[col + 1]) / 2;
    double y_pos = (field_square_y[row] + field_square_y[row + 1]) / 2;
    x_pos *= scale_x;
    y_pos *= scale_y;
    if (adding_sprite == MELONPULT)
        x_pos += MELONPULT_MARGIN ; 
    add_plant(adding_sprite, x_pos, y_pos);
}

void Handler::add_sprite(SpriteType sprite_type ,int x ,int y){
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

SpriteType Handler::get_random_zombie_type(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    if (giant_probability <= 0) 
        return REGULAR ; 
    int rand_num = rng() % 150 ;
    if (rand_num + 1 <= giant_probability)
       return HAIRMETALGARGANTUAR ;  
    return REGULAR ;
}

void Handler::generate_zombie(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= zombie_generate_duration) 
        return ;
    if (zombie_amount_per_cycle > 0){
        float needed_time_to_release_new_zombie = zombie_cycle_time / zombie_amount_per_cycle ; 
        //cout << needed_time_to_release_new_zombie << endl ;
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
    if (elapsed.asSeconds() >= zombie_cycle_time){
        last_zombie_increase_clock.restart() ; 
        zombie_amount_per_cycle += zombie_increase_rate ;
    }
}

void Handler::add_bullet(BulletType bullet_type ,int x ,int y){
    Bullet* bullet ; 
    switch (bullet_type){
    case PEA:
        bullet = new Pea_Bullet(x ,y ,bullet_type); 
        bullets.push_back(bullet);   
        break;
    case ICEPEA: 
        bullet = new Icepea_Bullet(x ,y ,bullet_type); 
        bullets.push_back(bullet) ; 
        break; 
    case MELLON: 
        bullet = new Mellon_Bullet(x ,y ,bullet_type); 
        bullets.push_back(bullet) ; 
        break ; 
    default:
        break;
    }
}

void Handler::handle_mouse_press(Event event, double scale_x, double scale_y)
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
        handle_adding_plant(event, adding_sprite, scale_x, scale_y);
    menu.handle_mouse_press(event, number_of_suns);
}

void Handler::render(RenderWindow &window)
{
    render_sun_bank(window);
    for (auto &game_object : game_objects)
        game_object->render(window) ; 
    for (auto &sun : suns)
        sun->render(window);
    for (auto &bullet : bullets)
        bullet->render(window) ; 
    menu.render(window);
    render_cursor_following_sprite(window);
}

void Handler::update()
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

void Handler::game_over_render(RenderWindow& window)
{
    render_sun_bank(window);
    for (auto &game_object : game_objects)
        game_object->render(window);
    for (auto &sun : suns)
        sun->render(window);
    menu.render(window);
}

void Handler::in_game_initialization()
{
    sun_generating_clock.restart();
}
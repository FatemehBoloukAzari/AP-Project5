#include "handler.h"
#include "setting.h"

const int THANKING_PERSON_HEIGHT = 835;
const int THANKING_PERSON_WIDTH = 375;

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

void Handler::add_plant(SpriteType sprite_type, double pos_x, double pos_y ,int row ,int col)
{
    Plant* new_plant = new Plant(pos_x, pos_y, sprite_type ,row ,col);
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
    add_plant(adding_sprite, x_pos, y_pos ,row ,col);
}

void Handler::add_zombie(SpriteType sprite_type ,double x ,double y ,int row_number){
    Zombie* zombie ; 
    switch (sprite_type){
    case REGULAR :
        zombie = new Zombie(x ,y ,sprite_type ,row_number) ; 
        game_objects.push_back(zombie) ;   
        break;
    case HAIRMETALGARGANTUAR: 
        zombie = new Zombie(x ,y ,sprite_type ,row_number) ; 
        game_objects.push_back(zombie) ;
        break; 
    default:
        break;
    }
    zombies_in_line[row_number].push_back(zombie) ;
}

SpriteType Handler::get_random_zombie_type(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    if (giant_probability <= 0) 
        return REGULAR ; 
    int rand_num = rng() % GIANT_PROBABILITY ;
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
        double needed_time_to_release_new_zombie = (double)zombie_cycle_time / zombie_amount_per_cycle ; 
        elapsed = last_zombie_spawn_clock.getElapsedTime() ; 
        if (elapsed.asSeconds() >= needed_time_to_release_new_zombie){
            SpriteType sprite_type = get_random_zombie_type() ;
            int row_number = rng() % NUM_ROW ;
            int y = row_spawn_height_giant[row_number] ;
            if (sprite_type == REGULAR)
                y = row_spawn_height_regular[row_number] ;
            add_zombie(sprite_type ,WIDTH ,y ,row_number) ; 
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

Zombie* Handler::first_zombie_in_row(double x, int row_number)
{
    Zombie* zombie = NULL;
    for (auto zm : zombies_in_line[row_number])
    {
        if (zm->get_x() < x)
            continue;
        if (zombie == NULL || zombie->get_x() > zm->get_x())
            zombie = zm;
    }
    return zombie;
}

void Handler::add_bullet(BulletType bullet_type ,int row_number ,double x ,double y){
    Bullet* bullet ; 
    switch (bullet_type){
    case PEA:
        bullet = new Pea_Bullet(row_number ,x ,y ,bullet_type); 
        bullets.push_back(bullet);
        break;
    case ICEPEA: 
        bullet = new Icepea_Bullet(row_number ,x ,y ,bullet_type); 
        bullets.push_back(bullet) ; 
        break; 
    case MELLON: 
    {
        Zombie* zombie = first_zombie_in_row(x, row_number);
        if (zombie == NULL)
            break;
        bullet = new Mellon_Bullet(row_number ,x ,y ,bullet_type, zombie); 
        bullets.push_back(bullet) ; 
        break ; 
    }
    case SUN:
    {
        Sun* new_sun = new Sun(NOT_MOVING_SUN, x, y);
        suns.push_back(new_sun);
        return;
    }
    default:
        break;
    }
    bullets_in_line[row_number].push_back(bullet);
}

void Handler::delete_bullet(Bullet* bullet){
    bullets.erase(find(bullets.begin() ,bullets.end() ,bullet)) ; 
    int row = bullet->get_row() ; 
    bullets_in_line[row].erase(find(bullets_in_line[row].begin() ,bullets_in_line[row].end() ,bullet));
    delete bullet ; 
}

void Handler::handle_mouse_press(Event event, double scale_x, double scale_y)
{
    for (int i = 0; i < (int)suns.size(); i++)
    {
        if (suns[i]->check_mouse_press(event))
        {
            auto save = suns[i];
            number_of_suns++;
            suns.erase(suns.begin() + i);
            i--;
            assert(save != NULL);
            delete save;
        }
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

int Handler::get_number_of_zombies()
{
    int cnt = 0;
    for (auto game_object : game_objects)
    {
        Zombie* zm = dynamic_cast<Zombie*> (game_object);
        if (zm != NULL)
            cnt++;
    }
    return cnt;
}



void Handler::update(State &state, double scale_x ,double scale_y)
{
    handle_plants_shooting() ; 
    handle_zombie_damages(scale_x ,scale_y) ; 
    clean_dead_plants() ; 
    check_moving_stopped_zombies(scale_x ,scale_y) ; 
    generate_random_sun() ; 
    clean_sun() ;
    clean_outside_bullets() ;
    check_peas_collision() ; 
    check_melons_collision();
    clean_dead_zombies() ; 
    menu.update();
    for (auto &game_object : game_objects)
    {
        game_object->update();
        Zombie* zm = dynamic_cast<Zombie*> (game_object);
        if (zm == NULL)
            continue;
        double x_pos = zm->get_x();
        if (x_pos < get_scaled_x(HOME_X, scale_x))
            state = GAMEOVER_SCREEN;
    }
    for (auto &bullet : bullets){
        bullet->update() ; 
    }
    Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= zombie_generate_duration && !get_number_of_zombies())
        state = VICTORY_SCREEN;
}

void Handler::game_over_render(RenderWindow& window)
{
    for (auto &game_object : game_objects)
        game_object->render(window);
    for (auto &sun : suns)
        sun->render(window);
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
    int y_pos = (HEIGHT - text.getLocalBounds().height) / 2 - 50;
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
    new_font.loadFromFile(FONTS_PATH + "HouseOfTerrorRegular.otf");
    text.setString("Press Escape To Exit");
    text.setCharacterSize(60);
    text.setFont(new_font);
    text.setFillColor(Color::White);
    x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    text.setPosition(x_pos, HEIGHT - 100);
    if (game_over_clock.getElapsedTime().asSeconds() > 8)
        window.draw(text);
}

void Handler::victory_render(RenderWindow& window)
{
    for (auto &game_object : game_objects)
        game_object->render(window);
    for (auto &sun : suns)
        sun->render(window);
    Texture thanking_person_texture;
    thanking_person_texture.loadFromFile(PICS_PATH + "winning_person.png");
    Sprite thanking_person;
    thanking_person.setTexture(thanking_person_texture);
    double scale_x = (double)THANKING_PERSON_WIDTH / thanking_person.getGlobalBounds().width;
    double scale_y = (double)THANKING_PERSON_HEIGHT / thanking_person.getGlobalBounds().height;
    thanking_person.setScale(scale_x, scale_y);
    thanking_person.setOrigin(thanking_person.getGlobalBounds().width / 2, thanking_person.getGlobalBounds().height / 2);
    thanking_person.setPosition(150, 300);
    window.draw(thanking_person);
    Font new_font;
    Text text;
    new_font.loadFromFile(FONTS_PATH + "HouseOfTerrorRegular.otf");
    text.setString("Press Escape To Exit");
    text.setCharacterSize(60);
    text.setFont(new_font);
    text.setFillColor(Color::White);
    int x_pos = (WIDTH - text.getLocalBounds().width) / 2;
    text.setPosition(x_pos, HEIGHT - 100);
    if (game_over_clock.getElapsedTime().asSeconds() > 8)
        window.draw(text);
}

void Handler::in_game_initialization()
{
    sun_generating_clock.restart();
}

void Handler::handle_plants_shooting(){
    for (auto object : game_objects){
        if (object->is_plant()){
            Plant* plant = dynamic_cast<Plant*>(object) ;
            if (zombies_in_line[plant->get_row()].empty() && plant->get_sprite_type() != SUNFLOWER){
                plant->shooting = false ; 
            }
            else {
                if (!plant->shooting && plant->get_sprite_type() != SUNFLOWER){
                    plant->shooting = true ; 
                    plant->shooted = false ; 
                    plant->init_shot_clock() ; 
                }
                plant->update() ; 
                if (plant->shooted){
                    plant->shooted = false ; 
                    switch (plant->get_sprite_type()){
                    case PEASHOOTER:
                        add_bullet(PEA ,plant->get_row() ,plant->get_x() ,plant->get_y() + BULLET_MARGIN);
                        break;
                    case SNOWPEA:
                        add_bullet(ICEPEA ,plant->get_row() ,plant->get_x() ,plant->get_y() + BULLET_MARGIN );
                        break; 
                    case MELONPULT:
                        add_bullet(MELLON ,plant->get_row() ,plant->get_x() ,plant->get_y() + BULLET_MARGIN);
                        break; 
                    case SUNFLOWER:
                        add_bullet(SUN, plant->get_row(), plant->get_x(), plant->get_y());
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}
void Handler::game_over_initialization()
{
    game_over_clock.restart();
}

void Handler::handle_zombie_damages(double scale_x ,double scale_y){
    for (auto it = game_objects.begin(); it != game_objects.end() ;it++){
        if ((*it)->is_plant()){
            auto plant = dynamic_cast<Plant*>(*it) ; 
            for (auto zombie : zombies_in_line[plant->get_row()]){
                if (is_in_same_field(zombie ,plant ,scale_x ,scale_y)){
                    if (!zombie->moving){
                        zombie->update() ;
                        if (zombie->attacked){
                            plant->decrease_health(zombie->get_damage()) ; 
                            zombie->attacked = false ; 
                        }
                    }
                    else {
                        zombie->moving = false ;
                        zombie->init_hit_clock() ; 
                    }
                }
            }
        }
    }
}

void Handler::clean_dead_plants(){
    for (auto it = game_objects.begin(); it != game_objects.end();){
        if ((*it)->is_plant()){
            auto plant = dynamic_cast<Plant*>(*it) ; 
            if (plant->is_dead()){
                square_is_full[plant->get_row()][plant->get_column()] = false ;
                delete plant ; 
                it = game_objects.erase(it) ; 
            }
            else {
                it++ ; 
            }
        }
        else {
            it++ ; 
        }
    }
}

void Handler::check_moving_stopped_zombies(double scale_x ,double scale_y){
    for (int row = 0; row < NUM_ROW; row++){
        for (auto zombie : zombies_in_line[row]){
            if (!zombie->moving){
                int col = zombie->get_column_number(scale_x ,scale_y) ;
                if (!square_is_full[row][col]){
                    zombie->moving = true ; 
                }
            }
        }
    }
}

void Handler::clean_sun(){
    for (int i = 0; i < (int)suns.size(); i++)
    {
        suns[i]->update();
        if (suns[i]->exited_screen())
        {
            auto save = suns[i];
            suns.erase(suns.begin() + i);
            i--;
            assert(save != NULL);
            delete save;
        }
    }
}

void Handler::clean_outside_bullets(){
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        (*it)->update();
        if ((*it)->exited_screen())
        {
            Bullet* exited_bullet = *it;
            int row = exited_bullet->get_row() ; 
            bullets_in_line[row].erase(find(bullets_in_line[row].begin() ,bullets_in_line[row].end(), exited_bullet));
            it = bullets.erase(it);
            delete exited_bullet;
        }
        else
            it++;
    }
}

void Handler::clean_dead_zombies(){
    vector <Zombie*> trash_zombies; 
    for (int row = 0; row < NUM_ROW; row++){
        for (auto zombie : zombies_in_line[row]){
            if (zombie->is_dead()){
                trash_zombies.push_back(zombie) ; 
            }
        }
    }
    for (auto zombie : trash_zombies){
        game_objects.erase(find(game_objects.begin() ,game_objects.end() ,zombie)) ; 
        int row = zombie->get_row() ; 
        zombies_in_line[row].erase(find(zombies_in_line[row].begin() ,zombies_in_line[row].end() ,zombie)) ; 
        delete zombie ; 
    }
}

void Handler::generate_random_sun(){
    Time elapsed = sun_generating_clock.getElapsedTime();
    if (elapsed.asSeconds() >= sun_interval)
    {
        sun_generating_clock.restart();
        Sun *new_sun = new Sun(MOVING_SUN);
        suns.push_back(new_sun);
    }
}

Zombie* find_zombie(vector <Zombie*> &zombies, Zombie* zombie)
{
    for (auto zm : zombies)
        if (zm == zombie)
            return zm;
    return NULL;
}

void Handler::check_melons_collision()
{
    vector <Bullet*> trash_bullets ;
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (auto bullet : bullets_in_line[row])
        {
            if (bullet->get_bullet_type() != MELLON)
                continue;
            Mellon_Bullet *melon = dynamic_cast<Mellon_Bullet*>(bullet);
            if (melon->end_collision_time())
            {
                Zombie* zombie = find_zombie(zombies_in_line[row], melon->get_target_zombie());
                if (zombie != NULL)
                    zombie->decrease_health(bullet->get_damage());
                trash_bullets.push_back(bullet);
            }
        }
    }
    for (auto bullet : trash_bullets){
        delete_bullet(bullet) ; 
    }
}

void Handler::check_peas_collision(){
    vector <Bullet*> trash_bullets ; 
    for (int row = 0; row < NUM_ROW; row++){
        for (auto bullet : bullets_in_line[row]){
            Zombie* nearest_zombie = NULL ; 
            for (auto zombie : zombies_in_line[row]){
                FloatRect zombie_rect = zombie->get_rect();
                FloatRect bullet_rect = bullet->get_rect();
                if (bullet_rect.intersects(zombie_rect)){
                    if (nearest_zombie == NULL || nearest_zombie->get_x() > zombie->get_x()){
                        nearest_zombie = zombie ; 
                    }
                }
            }
            if (nearest_zombie != NULL){
                switch (bullet->get_bullet_type()){
                case PEA:
                    nearest_zombie->decrease_health(bullet->get_damage()) ; 
                    trash_bullets.push_back(bullet) ; 
                    break;
                case ICEPEA:
                    nearest_zombie->decrease_health(bullet->get_damage()) ; 
                    nearest_zombie->affect_freezing() ; 
                    trash_bullets.push_back(bullet) ; 
                    break;                 
                default:
                    break;
                }    
            }
        }
    }
    for (auto bullet : trash_bullets){
        delete_bullet(bullet) ; 
    }
}

bool Handler::is_in_same_field(Zombie *zombie, Plant *plant ,double scale_x ,double scale_y){
    return plant->get_column() == zombie->get_column_number(scale_x ,scale_y) ;
}

#include "setting.h"

string get_sprite_string(SpriteType sprite_type)
{
    switch (sprite_type)
    {
        case WALNUT:
            return WALNUT_STRING;
        case PEASHOOTER:
            return PEASHOOTER_STRING;
        case SNOWPEA:
            return SNWOPEA_STRING;
        case MELONPULT:
            return MELONPULT_STRING;
        case SUNFLOWER:
            return SUNFLOWER_STRING;
        case REGULAR:
            return REGULAR_STRING;
        case HAIRMETALGARGANTUAR:
            return HAIRMETALGARGANTUAR_STRING;
        default:
            break;
    }
    return EMPTY_STRING;
}

vector <string> dash_split(string str)
{
    vector <string> ret;
    string cur_str = EMPTY_STRING;
    for (auto c : str)
    {
        if (c == DASH || c == COMMA)
        {
            ret.push_back(cur_str);
            cur_str = EMPTY_STRING;
        }
        else
            cur_str += c;
    }
    if (cur_str != EMPTY_STRING)
        ret.push_back(cur_str);
    return ret;
}

vector <string> get_setting(string sprite_str)
{
    ifstream setting_file(SETTING_FILE);
    string str;
    while (setting_file >> str)
    {
        if (str == ZOMBIES_STRING || str == PLANTS_STRING || str == ATTACKS_STRING || str == SUN_STRING)
            continue;
        vector <string> splited_str = dash_split(str);
        if (splited_str[0] == sprite_str)
        {
            setting_file.close();
            return splited_str;
        }
    }
    return {};
}

bool have_sprite_in_setting(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    if (sprite_setting.empty())
        return false;
    return true;
}

int read_zombie_damage_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[1]);
}

int read_zombie_health_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[2]);
}

int read_zombie_hit_rate_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[3]);
}

int read_zombie_speed_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[4]);
}


int read_plant_damage_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[1]);
}

int read_plant_health_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[2]);
}

int read_plant_cooldown_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[3]);
}

int read_plant_hit_rate_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[4]);
}

int read_plant_speed_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[5]);
}

int read_plant_price_from_file(SpriteType sprite_type)
{
    vector <string> sprite_setting = get_setting(get_sprite_string(sprite_type));
    return stoi(sprite_setting[6]);
}


int read_total_attack_time()
{
    vector <string> sprite_setting = get_setting("attack");
    return stoi(sprite_setting[1]);
}

int read_attack_interval()
{
    vector <string> sprite_setting = get_setting("attack");
    return stoi(sprite_setting[2]);

}

int read_first_interval_zombies()
{
    vector <string> sprite_setting = get_setting("attack");
    return stoi(sprite_setting[3]);
}

int read_zombie_number_change()
{
    vector <string> sprite_setting = get_setting("attack");
    return stoi(sprite_setting[4]);
}


int read_sun_speed_from_file()
{
    vector <string> sprite_setting = get_setting("sun");
    return stoi(sprite_setting[1]);
}

int read_sun_interval_from_file()
{
    vector <string> sprite_setting = get_setting("sun");
    return stoi(sprite_setting[2]);
}
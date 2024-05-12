#include "setting.h"

string get_sprite_string(SpriteType sprite_type)
{
    switch (sprite_type)
    {
        case WALNUT:
            return "walnut";
        case PEASHOOTER:
            return "peashooter";
        case SNOWPEA:
            return "snowpea";
        case MELONPULT:
            return "melonPult";
        case SUNFLOWER:
            return "sunflower";
        case REGULAR:
            return "regular";
        case HAIRMETALGARGANTUAR:
            return "hairMetalGargantuar";
        default:
            break;
    }
    return "";
}

vector <string> dash_split(string str)
{
    vector <string> ret;
    string cur_str = "";
    for (auto c : str)
    {
        if (c == '-' || c == ',')
        {
            ret.push_back(cur_str);
            cur_str = "";
        }
        else
            cur_str += c;
    }
    if (cur_str != "")
        ret.push_back(cur_str);
    return ret;
}

vector <string> get_setting(string sprite_str)
{
    ifstream setting_file(SETTING_FILE);
    string str;
    while (setting_file >> str)
    {
        if (str == "ZOMBIES:" || str == "PLANTS:" || str == "ATTACKS:" || str == "SUN:")
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
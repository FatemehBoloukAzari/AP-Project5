#include "setting.h"
#include <fstream>

int WALNUT_CARD_COOLDOWN;
int PEASHOOTER_CARD_COOLDOWN;
int SNOWPEA_CARD_COOLDOWN;
int MELONPULT_CARD_COOLDOWN;
int SUNFLOWER_CARD_COOLDOWN;

int WALNUT_PRICE;
int PEASHOOTER_PRICE;
int SNOWPEA_PRICE;
int MELONPULT_PRICE;
int SUNFLOWER_PRICE;

int SUN_SPEED;
int SUN_INTERVAL;

SpriteType get_sprite_type(string type_str)
{
    if (type_str == "walnut")
        return WALNUT;
    if (type_str == "peashooter")
        return PEASHOOTER;
    if (type_str == "snowpea")
        return SNOWPEA;
    if (type_str == "melonPult")
        return MELONPULT;
    if (type_str == "sunflower")
        return SUNFLOWER;
    if (type_str == "regular")
        return REGULAR;
    if (type_str == "hairMetalGargantuar")
        return HAIRMETALGARGANTUAR;
    return NOT_SPRITE;
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

void set_zombies(ifstream &setting_file)
{
    string str;
    setting_file >> str;
    do
    {
        setting_file >> str;
        vector <string> splited_str = dash_split(str);
        SpriteType type = get_sprite_type(splited_str[0]);
        switch (type)
        {
            case REGULAR:
                // set value of global variables for regular zombie
                break;
            case HAIRMETALGARGANTUAR:
                // set value of global variables for hairmetal zombie
                break;
            default:
                break;
            
        }
    } while (str != "PLANTS:");
}

void set_plants(ifstream &setting_file)
{
    string str;
    do
    {
        setting_file >> str;
        vector <string> splited_str = dash_split(str);
        SpriteType type = get_sprite_type(splited_str[0]);
        switch (type)
        {
            case WALNUT:
                // damage
                // health
                WALNUT_CARD_COOLDOWN = stoi(splited_str[3]);
                // hit rate
                // speed
                WALNUT_PRICE = stoi(splited_str[6]);
                break;
            case PEASHOOTER:
                // damage
                // health
                PEASHOOTER_CARD_COOLDOWN = stoi(splited_str[3]);
                // hit rate
                // speed
                PEASHOOTER_PRICE = stoi(splited_str[6]);
                break;
            case SNOWPEA:
                // damage
                // health
                SNOWPEA_CARD_COOLDOWN = stoi(splited_str[3]);
                // hit rate
                // speed
                SNOWPEA_PRICE = stoi(splited_str[6]);
                break;
            case MELONPULT:
                // damage
                // health
                MELONPULT_CARD_COOLDOWN = stoi(splited_str[3]);
                // hit rate
                // speed
                MELONPULT_PRICE = stoi(splited_str[6]);
                break;
            case SUNFLOWER:
                // damage
                // health
                SUNFLOWER_CARD_COOLDOWN = stoi(splited_str[3]);
                // hit rate
                // speed
                SUNFLOWER_PRICE = stoi(splited_str[6]);
                break;
            default:
                break;
        }
    } while (str != "ATTACKS:");
}

void set_attack(ifstream &setting_file)
{
    string str;
    do
    {
        setting_file >> str;
        vector <string> splited_str = dash_split(str);
        // total attack time
        // each time block
        // number of zomibes in the first time block
        // number of zombies increased in each time block
    } while (str != "SUN:");
}

void set_sun(ifstream &setting_file)
{
    string str;
    setting_file >> str;
    vector <string> splited_str = dash_split(str);
    SUN_SPEED = stoi(splited_str[0]);
    SUN_INTERVAL = stoi(splited_str[1]);
}

void set_setting()
{
    ifstream setting_file("setting.txt");
    if (!setting_file.is_open())
    {
        cerr << "FILE_OPENING_ERROR" << endl;
        exit(0);
    }
    set_zombies(setting_file);
    set_plants(setting_file);
    set_attack(setting_file);
    set_sun(setting_file);
    setting_file.close();
}
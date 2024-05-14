#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <cstring> 
#include <set>
#include <assert.h>

using namespace std;
using namespace sf;

enum BulletType 
{
    PEA, 
    ICEPEA,
    MELLON,
    SUN
}; 

enum SpriteType
{
    WALNUT,
    PEASHOOTER,
    SNOWPEA,
    MELONPULT,
    SUNFLOWER,
    NOT_SPRITE,
    REGULAR,
    HAIRMETALGARGANTUAR,
};

enum State
{
    MAIN_MENU,
    IN_GAME,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    EXIT
};

const int WIDTH = 1500;
const int HEIGHT = 1000;
const int FRAME_RATE = 72;
const int NUM_ROW = 5 ; 
const int NUM_COLUMN = 10 ;

const string PICS_PATH = "./files/pics/";
const string AUDIO_PATH = "./files/audios/";
const string FONTS_PATH = "./files/fonts/";
const string SETTING_FILE = "setting.txt";

const int field_square_x[] = {220, 288, 351, 426, 490, 561, 634, 697, 763, 840};
const int field_square_y[] = {67, 154, 233, 322, 399, 483};
const int HOME_X = 173;

const int row_spawn_height_regular[] = {100 ,245 ,420 ,600 ,755} ; 
const int row_spawn_height_giant[] = {20 ,180 ,370 ,530 ,703} ;

const int INITIAL_NUMBER_OF_SUNS = 3;

const bool MOVING_SUN = true;
const bool NOT_MOVING_SUN = false;

const int MELONPULT_MARGIN = -35 ;
const int ZOMBIE_EATING_MARGIN = -53 ; 
const int BULLET_MARGIN = -30 ; 
const int GENERATED_SUN_MARGIN_X = -50 ; 
const int GENERATED_SUN_MARGIN_Y = -50 ; 

const pair <int, int> NO_SQUARE = {-1, -1};

const int CARD_WIDTH = 160;
const int CARD_HEIGHT = 100;
const int MOVING_SPRITE_WIDTH = 100;
const int MOVING_SPRITE_HEIGHT = 100;
const int SUN_BANK_WIDTH = 250;
const int SUN_BANK_HEIGHT = 75;
const int SUNFLOWER_WIDTH = 120;
const int SUNFLOWER_HEIGHT = 125; 
const int PEASHOOTER_WIDTH = 120; 
const int PEASHOOTER_HEIGHT = 125; 
const int SNOWPEA_WIDTH = 135; 
const int SNOWPEA_HEIGHT = 110; 
const int WALNUT_WIDTH = 100; 
const int WALNUT_HEIGHT = 120; 
const int MELONPULT_WIDTH = 200; 
const int MELONPULT_HEIGHT = 140; 
const int REGULAR_WIDTH = 110;
const int REGULAR_HEIGHT = 180; 
const int HAIRMETALGARGANTUAR_WIDTH = 240; 
const int HAIRMETALGARGANTUAR_HEIGHT = 250; 
const int PEA_BULLET_WIDTH = 40 ; 
const int PEA_BULLET_HEIGHT = 40 ; 
const int ICEPEA_BULLET_WIDTH = 40 ; 
const int ICEPEA_BULLET_HEIGHT = 40 ; 
const int MELLON_BULLET_WIDTH = 70 ; 
const int MELLON_BULLET_HEIGHT = 61 ;
const int SUN_WIDTH = 100;
const int SUN_HEIGHT = 100;
const int THANKING_PERSON_HEIGHT = 835;
const int THANKING_PERSON_WIDTH = 375;

const int X_SPACE = 350;

const int SUN_MOVE_INTERVAL = 10;
const int ZOMBIE_MOVE_INTERVAL = 30; 
const int PEA_BULLET_MOVE_INTERVAL = 30 ;
const int ICEPEA_BULLET_MOVE_INTERVAL = 30 ;
const int ZOMBIE_GROAN_INTERVAL = 5 ; 

const int GIANT_PROBABILITY = 175 ; 

const int FREEZE_TIME_PER_BULLET = 5 ; 

const int SCALE_MILLISECONDS = 100 ;

const int SUNBULLET_SPEED = 30 ;

const double SUN_FINAL_DELTA_X = 60 ;
const double SUN_EXTRA_DELTA_X = 4 ; 

const double SUN_ACCELERATION = 0.15 ;
const int MELLON_ACCELERATION = 2000 ;

const int SUNFLOWER_SUN_SPEED = 40 ; 

const int NUM_ZOMBIE_GROAN = 6 ;
const Color FROZEN_COLOR = Color(100, 100, 255) ; 

const string EMPTY_STRING = "" ; 
const char DASH = '-' ; 
const char COMMA = ',' ; 
const string ZOMBIES_STRING = "ZOMBIES:" ; 
const string PLANTS_STRING = "PLANTS:" ; 
const string ATTACKS_STRING = "ATTACKES:" ; 
const string SUN_STRING = "SUN:" ; 
const string WALNUT_STRING = "walnut" ; 
const string PEASHOOTER_STRING = "peashooter" ; 
const string SNWOPEA_STRING = "snowpea" ; 
const string MELONPULT_STRING = "melonPult" ; 
const string SUNFLOWER_STRING = "sunflower" ; 
const string REGULAR_STRING = "regular" ; 
const string HAIRMETALGARGANTUAR_STRING = "hairMetalGargantuar" ; 

const int MENU_Y = 100 ; 
const int MENU_X = 20 ; 
const int MENU_SPACE_Y = 3 ; 

const int CARD_NORMAL_RENDER_TEXT_CHARACTER_SIZE = 35 ;
const int CARD_NORMAL_RENDER_TEXT_MARGIN_X = 123 ;
const int CARD_NORMAL_RENDER_TEXT_MARGIN_Y = 50 ;
const int CARD_COOLDOWN_RENDER_TEXT_MARGIN_X = 60 ;
const int CARD_COOLDOWN_RENDER_TEXT_MARGIN_Y = 25 ;

const float GRAY_R = 0.2126f ; 
const float GRAY_G = 0.7152f ; 
const float GRAY_B = 0.0722f ;

const int GAME_OVER_DRAW_TIME = 8 ; 
const int VICTORY_Y_MARGIN = 100 ; 
const int VICTORY_TEXT_SIZE = 60 ;

const int THANKING_PERSON_X_POS = 150 ; 
const int THANKING_PERSON_y_POS = 300 ; 


#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;
using namespace sf;

enum BulletType 
{
    PEA, 
    ICEPEA,
    MELLON
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

const int WIDTH = 1500;
const int HEIGHT = 1000;
const int FRAME_RATE = 72;
const int NUM_ROW = 5 ; 
const int NUM_COLUMN = 9 ;

const string PICS_PATH = "./files/pics/";
const string AUDIO_PATH = "./files/audios/";
const string FONTS_PATH = "./files/fonts/";
const string SETTING_FILE = "setting.txt";

const int COLUMN = 9;
const int ROW = 5;

const int field_square_x[] = {220, 288, 351, 426, 490, 561, 634, 697, 763, 840};
const int field_square_y[] = {67, 154, 233, 322, 399, 483};
extern bool square_is_full[ROW][COLUMN];

const int row_spawn_height_regular[] = {100 ,245 ,420 ,600 ,755} ; 
const int row_spawn_height_giant[] = {20 ,180 ,370 ,530 ,703} ;

extern int ZOMBIE_SPEED ; 
extern int ZOMBIE_MOVE_INTERVAL ; 

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
const int PEA_BULLET_WIDTH = 20 ; 
const int PEA_BULLET_HEIGHT = 20 ; 
const int ICEPEA_BULLET_WIDTH = 20 ; 
const int ICEPEA_BULLET_HEIGHT = 20 ; 
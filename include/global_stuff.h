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

const int INITIAL_NUMBER_OF_SUNS = 100;

const bool MOVING_SUN = true;
const bool NOT_MOVING_SUN = false;

const int MELONPULT_MARGIN = -35 ;
const int ZOMBIE_EATING_MARGIN = -53 ; 
const int BULLET_MARGIN = -30 ; 

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

const int X_SPACE = 350;

const int SUN_MOVE_INTERVAL = 10;
const int ZOMBIE_MOVE_INTERVAL = 30; 
const int PEA_BULLET_MOVE_INTERVAL = 30 ;
const int ICEPEA_BULLET_MOVE_INTERVAL = 30 ;

const int GIANT_PROBABILITY = 450 ; 

/*
void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << H ;
	debug_out(T...);
}
 
#define debug(...)             cerr << "(" << #__VA_ARGS__ << "): ", debug_out(__VA_ARGS__)
*/
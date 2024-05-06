#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum SpriteType
{
    WALNUT,
    PEASHOOTER,
    SNOWPEA,
    MELONPULT,
    SUNFLOWER,
    NOT_SPRITE
};

const int WIDTH = 1500;
const int HEIGHT = 1000;
const int FRAME_RATE = 72;

const string PICS_PATH = "./files/pics/";
const string AUDIO_PATH = "./files/audios/";
const string FONTS_PATH = "./files/fonts/";

const int field_square_x[] = {220, 288, 351, 426, 490, 561, 634, 697, 763, 840};
const int field_square_y[] = {67, 154, 233, 322, 399, 483};

extern int WALNUT_CARD_COOLDOWN; // change it to value in setting file
extern int PEASHOOTER_CARD_COOLDOWN;
extern int SNOWPEA_CARD_COOLDOWN;
extern int MELONPULT_CARD_COOLDOWN;
extern int SUNFLOWER_CARD_COOLDOWN;

extern int WALNUT_PRICE; // change it to value in setting file
extern int PEASHOOTER_PRICE;
extern int SNOWPEA_PRICE;
extern int MELONPULT_PRICE;
extern int SUNFLOWER_PRICE;
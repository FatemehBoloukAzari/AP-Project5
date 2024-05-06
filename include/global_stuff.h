#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

const int WIDTH = 1500;
const int HEIGHT = 1000;
const int FRAME_RATE = 72;

const string PICS_PATH = "./files/pics/";
const string AUDIO_PATH = "./files/audios/";
const string FONTS_PATH = "./files/fonts/";

const int field_square_x[] = {220, 288, 351, 426, 490, 561, 634, 697, 763, 840};
const int field_square_y[] = {67, 154, 233, 322, 399, 483};

const int WALNUT_CARD_COOLDOWN = 3; // change it to value in setting file
const int PEASHOOTER_CARD_COOLDOWN = 5;
const int SNOWPEA_CARD_COOLDOWN = 7;
const int MELONPULT_CARD_COOLDOWN = 10;
const int SUNFLOWER_CARD_COOLDOWN = 12;
// they cause problem when they are not const
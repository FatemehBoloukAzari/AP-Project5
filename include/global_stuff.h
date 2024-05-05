#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

const int WIDTH = 2000;
const int HEIGHT = 1300;
const int FRAME_RATE = 72;

const string PICS_PATH = "./files/pics/";
const string AUDIO_PATH = "./files/audios/";
const string FONTS_PATH = "./files/fonts/";

int field_square_x[] = {220, 288, 351, 426, 490, 561, 634, 697, 763, 840};
int field_square_y[] = {67, 154, 233, 322, 399, 483};
/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef game_constants_h
#define game_constants_h

#include <string>
#include <stdint.h>

extern double ZOOM_RATE;
extern double ZOOM_MIN;
extern double ZOOM_MAX;

extern double TIME_SCALE;

extern double SPEED_OF_LIGHT;
extern double GRAVITY;

extern double SUPERMASSIVE_BLACK_HOLE_MASS;
extern double SUPERMASSIVE_BLACK_HOLE_DENSITY;
extern double SOLAR_MASS;
extern double SOLAR_DENSITY;
extern double EARTH_MASS;
extern double EARTH_DENSITY;
extern double MOON_MASS;
extern double MOON_DENSITY;

void set_game_constant(std::string name,std::string value);

#endif

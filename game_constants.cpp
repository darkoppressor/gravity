/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "game_constants.h"
#include "world.h"

using namespace std;

double ZOOM_RATE=0.0;
double ZOOM_MIN=0.0;
double ZOOM_MAX=0.0;

double TIME_SCALE=0.0;

double SPEED_OF_LIGHT=0.0;
double GRAVITY=0.0;

double SUPERMASSIVE_BLACK_HOLE_MASS=0.0;
double SUPERMASSIVE_BLACK_HOLE_DENSITY=0.0;
double SOLAR_MASS=0.0;
double SOLAR_DENSITY=0.0;
double EARTH_MASS=0.0;
double EARTH_DENSITY=0.0;
double MOON_MASS=0.0;
double MOON_DENSITY=0.0;

void set_game_constant(string name,string value){
    if(name=="zoom_rate"){
        ZOOM_RATE=Strings::string_to_double(value);
    }
    else if(name=="zoom_min"){
        ZOOM_MIN=Strings::string_to_double(value);
    }
    else if(name=="zoom_max"){
        ZOOM_MAX=Strings::string_to_double(value);
    }
    else if(name=="time_scale"){
        TIME_SCALE=Strings::string_to_double(value);
    }
    else if(name=="speed_of_light"){
        SPEED_OF_LIGHT=Strings::string_to_double(value);
    }
    else if(name=="gravity"){
        GRAVITY=Strings::string_to_double(value);
    }
    else if(name=="supermassive_black_hole_mass"){
        SUPERMASSIVE_BLACK_HOLE_MASS=Strings::string_to_double(value);
    }
    else if(name=="supermassive_black_hole_density"){
        SUPERMASSIVE_BLACK_HOLE_DENSITY=Strings::string_to_double(value);
    }
    else if(name=="solar_mass"){
        SOLAR_MASS=Strings::string_to_double(value);
    }
    else if(name=="solar_density"){
        SOLAR_DENSITY=Strings::string_to_double(value);
    }
    else if(name=="earth_mass"){
        EARTH_MASS=Strings::string_to_double(value);
    }
    else if(name=="earth_density"){
        EARTH_DENSITY=Strings::string_to_double(value);
    }
    else if(name=="moon_mass"){
        MOON_MASS=Strings::string_to_double(value);
    }
    else if(name=="moon_density"){
        MOON_DENSITY=Strings::string_to_double(value);
    }
}

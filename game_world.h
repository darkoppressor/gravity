/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef game_world_h
#define game_world_h

#include "particle.h"
#include "vector.h"
#include "collision.h"

#include <vector>

class Game_World{
public:

    double universe_mass;
    double universe_density;
    double universe_volume;

    std::vector<Particle> particles;

    std::vector <Collision> gravitations;

    int selected_particle;

    Game_World();

    void clear_world();
    void generate_world();

    void tick();
    void ai();
    void movement();
    void events();
    void animate();
    void render();

    void update_background();
    void render_background();
};

#endif

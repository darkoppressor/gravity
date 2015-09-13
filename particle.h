/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef particle_h
#define particle_h

#include "collision.h"
#include "vector.h"

class Particle{
public:

    double mass;
    double density;
    Collision_Circ circle;

    Vector velocity;
    Vector acceleration;
    Vector force;

    Particle(double get_mass,double get_density,double x,double y,Vector get_velocity);

    void accelerate();
    void movement(uint32_t index);
    void gravitate(uint32_t index);

    void render(int index);
};

#endif

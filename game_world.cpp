/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "game_world.h"
#include "world.h"
#include "render.h"

using namespace std;

Game_World::Game_World(){
    clear_world();
}

void Game_World::clear_world(){
    universe_mass=0.0;
    universe_density=0.0;
    universe_volume=0.0;

    particles.clear();

    gravitations.clear();

    selected_particle=-1;
}

void Game_World::generate_world(){
    clear_world();

	///
	int x=0;
	int y=0;

	double mass_sagittarius_a_star=8570650500000000000000000000000000000.0;
	double mass_sun=1988550000000000000000000000000.0;
	double mass_mercury=330000000000000000000000.0;
	double mass_venus=4870000000000000000000000.0;
	double mass_earth=5976000000000000000000000.0;
	double mass_mars=642000000000000000000000.0;
	double mass_jupiter=1900000000000000000000000000.0;
	double mass_saturn=569000000000000000000000000.0;
	double mass_uranus=87000000000000000000000000.0;
	double mass_neptune=103000000000000000000000000.0;
	double mass_pluto=10000000000000000000000.0;
	double mass_moon=73477000000000000000000.0;
	double mass_phobos=10659000000000000.0;
	double mass_deimos=1476200000000000.0;

	double density_sagittarius_a_star=192157408798087.57120425218505689;
	double density_sun=1408000000000.0;
	double density_mercury=5420000000000.0;
	double density_venus=5240000000000.0;
	double density_earth=5500000000000.0;
	double density_mars=3940000000000.0;
	double density_jupiter=1314000000000.0;
	double density_saturn=700000000000.0;
	double density_uranus=1300000000000.0;
	double density_neptune=1660000000000.0;
	double density_pluto=2000000000000.0;
	double density_moon=3346400000000.0;
	double density_phobos=1876000000000.0;
	double density_deimos=1471000000000.0;

	double distance_sun=270000000000000000.0;
	double distance_mercury=57900000.0;
	double distance_venus=108200000.0;
	double distance_earth=149600000.0;
	double distance_mars=227900000.0;
	double distance_jupiter=778300000.0;
	double distance_saturn=1426000000.0;
	double distance_uranus=2871000000.0;
	double distance_neptune=4497000000.0;
	double distance_pluto=5914000000.0;
	double distance_moon=384399.0;
	double distance_phobos=9376.0;
	double distance_deimos=23463.2;

	double velocity_sun=220.0;
	double velocity_mercury=47.9;
	double velocity_venus=35.0;
	double velocity_earth=29.8;
	double velocity_mars=24.1;
	double velocity_jupiter=13.1;
	double velocity_saturn=9.6;
	double velocity_uranus=6.8;
	double velocity_neptune=5.4;
	double velocity_pluto=4.7;
	double velocity_moon=1.022;
	double velocity_phobos=2.138;
	double velocity_deimos=1.3513;

	particles.push_back(Particle(mass_sagittarius_a_star,density_sagittarius_a_star,x,y,Vector(0.0,0.0)));

	particles.push_back(Particle(mass_sun,density_sun,x+distance_sun,y,Vector(velocity_sun,90.0)));

	particles.push_back(Particle(mass_mercury,density_mercury,x+distance_sun+distance_mercury,y,Vector(velocity_sun+velocity_mercury,90.0)));
	particles.push_back(Particle(mass_venus,density_venus,x+distance_sun+distance_venus,y,Vector(velocity_sun+velocity_venus,90.0)));
	particles.push_back(Particle(mass_earth,density_earth,x+distance_sun+distance_earth,y,Vector(velocity_sun+velocity_earth,90.0)));
	particles.push_back(Particle(mass_mars,density_mars,x+distance_sun+distance_mars,y,Vector(velocity_sun+velocity_mars,90.0)));
	particles.push_back(Particle(mass_jupiter,density_jupiter,x+distance_sun+distance_jupiter,y,Vector(velocity_sun+velocity_jupiter,90.0)));
	particles.push_back(Particle(mass_saturn,density_saturn,x+distance_sun+distance_saturn,y,Vector(velocity_sun+velocity_saturn,90.0)));
	particles.push_back(Particle(mass_uranus,density_uranus,x+distance_sun+distance_uranus,y,Vector(velocity_sun+velocity_uranus,90.0)));
	particles.push_back(Particle(mass_neptune,density_neptune,x+distance_sun+distance_neptune,y,Vector(velocity_sun+velocity_neptune,90.0)));
	particles.push_back(Particle(mass_pluto,density_pluto,x+distance_sun+distance_pluto,y,Vector(velocity_sun+velocity_pluto,90.0)));

	particles.push_back(Particle(mass_moon,density_moon,x+distance_sun+distance_earth+distance_moon,y,Vector(velocity_sun+velocity_earth+velocity_moon,90.0)));

	particles.push_back(Particle(mass_phobos,density_phobos,x+distance_sun+distance_mars+distance_phobos,y,Vector(velocity_sun+velocity_mars+velocity_phobos,90.0)));
	particles.push_back(Particle(mass_deimos,density_deimos,x+distance_sun+distance_mars+distance_deimos,y,Vector(velocity_sun+velocity_mars+velocity_deimos,90.0)));

	game.world.selected_particle=4;
	///

    /**universe_mass=SOLAR_MASS*20.0;
    universe_density=(SOLAR_MASS*0.004)/pow(SPEED_OF_LIGHT*31556900.0,3.0);
    universe_volume=universe_mass/universe_density;
    double universe_radius=pow(universe_volume*(3.0/(4.0*PI)),1.0/3.0);

    for(double mass_to_create=universe_mass;mass_to_create>0.0;){
        double mass=(double)game.rng.weighted_random_range(100,100000,100,"very_strong")*0.001*SOLAR_MASS;
        double density=(double)game.rng.weighted_random_range(9,11,10,"very_strong")*0.1*SOLAR_DENSITY;

        Vector position((double)game.rng.random_range(0,1000000000)*0.000000001*universe_radius,(double)game.rng.random_range(0,359));
        Vector_Components vc=position.get_components_absolute();

        particles.push_back(Particle(mass,density,vc.a,vc.b,Vector(0.0,0.0)));

        mass_to_create-=mass;
    }*/

    ///game.center_camera(Collision_Circ(0.0,0.0,0.0));
}

void Game_World::tick(){
}

void Game_World::ai(){
}

void Game_World::movement(){
    for(int i=0;i<particles.size();i++){
        particles[i].accelerate();
    }

    for(int i=0;i<particles.size();i++){
        particles[i].movement(i);
    }

    for(int i=0;i<gravitations.size();i++){
        particles[gravitations[i].object1].gravitate(gravitations[i].object2);
    }
    gravitations.clear();
}

void Game_World::events(){
}

void Game_World::animate(){
}

void Game_World::render(){
    for(int i=0;i<particles.size();i++){
        particles[i].render(i);
    }
}

void Game_World::update_background(){
}

void Game_World::render_background(){
    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"ui_black");
}

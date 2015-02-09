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

    game.center_camera(Collision_Circ(0.0,0.0,0.0));
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

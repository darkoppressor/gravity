/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "particle.h"
#include "world.h"
#include "render.h"

using namespace std;

Particle::Particle(double get_mass,double get_density,double x,double y,Vector get_velocity){
    mass=get_mass;
    density=get_density;

    double volume=mass/density;
    double radius=pow(volume*(3.0/(4.0*PI)),1.0/3.0);

    circle=Collision_Circ(x,y,radius);
    velocity=get_velocity;
}

void Particle::accelerate(){
    acceleration=force/mass;

    velocity+=acceleration*TIME_SCALE/UPDATE_RATE;

    force*=0.0;
}

void Particle::movement(uint32_t index){
    Vector_Components vc=velocity.get_components();

    circle.x+=vc.a*TIME_SCALE/UPDATE_RATE;
    circle.y+=vc.b*TIME_SCALE/UPDATE_RATE;

    for(int i=0;i<game.world.particles.size();i++){
        Particle* particle=&game.world.particles[i];

        if(this!=particle){
            uint32_t object1=0;
            uint32_t object2=0;
            if(index<=i){
                object1=index;
                object2=i;
            }
            else{
                object1=i;
                object2=index;
            }

            Collision gravitation(object1,object2);

            bool interaction_is_old=false;
            for(int j=0;j<game.world.gravitations.size();j++){
                if(gravitation==game.world.gravitations[j]){
                    interaction_is_old=true;
                    break;
                }
            }

            if(!interaction_is_old){
                game.world.gravitations.push_back(gravitation);
            }

            if(collision_check_circ(circle,particle->circle)){
                Vector collision(particle->circle.r+circle.r,get_angle_to_circ(particle->circle,circle,game.camera));
                Vector_Components vc_coll=collision.get_components();
                circle.x=particle->circle.x+vc_coll.a;
                circle.y=particle->circle.y+vc_coll.b;
            }
        }
    }
}

void Particle::gravitate(uint32_t index){
    Particle* particle=&game.world.particles[index];

    double distance=distance_between_points(circle.x,circle.y,particle->circle.x,particle->circle.y);

    double force_magnitude=(GRAVITY*mass*particle->mass)/pow(distance,2.0);

    force+=Vector(force_magnitude,get_angle_to_circ(circle,particle->circle,game.camera));
    particle->force+=Vector(force_magnitude,get_angle_to_circ(particle->circle,circle,game.camera));
}

void Particle::render(int index){
    if(collision_check_circ_rect(circle*game.camera_zoom,game.camera)){
        double radius=circle.r*game.camera_zoom;
        if(radius<0.5){
            radius=0.5;
        }

        render_circle(circle.x*game.camera_zoom-game.camera.x,circle.y*game.camera_zoom-game.camera.y,radius,1.0,"white");

        if(game.show_particle_data || index==game.world.selected_particle){
            Bitmap_Font* font=engine_interface.get_font("standard");

            double text_scale=game.camera_zoom;
            if(text_scale<0.6){
                text_scale=0.6;
            }

            string msg="";
            msg+="Mass: "+Strings::num_to_string(mass)+" kg"+"\n";
            msg+="Density: "+Strings::num_to_string(density)+" kg/km"+string(1,(unsigned char)252)+"\n";
            ///msg+="Volume: "+Strings::num_to_string()+""+"\n";
            msg+="Radius: "+Strings::num_to_string(circle.r)+" km"+"\n";
            ///msg+="Position: "+Strings::num_to_string(circle.x)+","+Strings::num_to_string(circle.y)+"\n";
            msg+="Velocity: "+Strings::num_to_string(velocity.magnitude)+" km/s ("+Strings::num_to_string(velocity.magnitude/SPEED_OF_LIGHT)+" c) "+Strings::num_to_string(velocity.direction)+string(1,(unsigned char)167)+"\n";
            msg+="Acceleration: "+Strings::num_to_string(acceleration.magnitude)+" km/s"+string(1,(unsigned char)253)+" "+Strings::num_to_string(acceleration.direction)+string(1,(unsigned char)167)+"\n";

            font->show((circle.x+circle.r/2.0)*game.camera_zoom-game.camera.x,(circle.y-circle.r/2.0)*game.camera_zoom-game.camera.y,msg,"red",1.0,text_scale,text_scale);
        }
    }
}

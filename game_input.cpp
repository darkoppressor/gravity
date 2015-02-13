#include "game.h"
#include "world.h"

using namespace std;

void Game::prepare_for_input(){
    if(in_progress){
        command_states.clear();

        touch_events.clear();

        display_scoreboard=false;
    }
}

void Game::handle_command_states_multiplayer(){
    if(in_progress){
        if(network.status=="server"){
            network.prepare_server_input_states();

            for(int i=0;i<network.clients.size();i++){
                if(!paused){
                    //Example multiplayer command state
                    /**if(network.clients[i].game_command_state("some_command")){
                        ///Deal with command state here
                    }*/
                }
            }
        }
    }
}

void Game::handle_game_commands_multiplayer(){
    if(in_progress){
        if(network.status=="server"){
            for(int i=0;i<network.clients.size();i++){
                for(int j=0;j<network.clients[i].command_buffer.size();j++){
                    string command_name=network.clients[i].command_buffer[j];

                    if(!paused){
                        //Example multiplayer command
                        /**if(command_name=="some_command"){
                            ///Deal with command here
                        }*/
                    }
                }

                network.clients[i].command_buffer.clear();
            }
        }
    }
}

void Game::handle_input_states_gui(){
    int mouse_x=0;
    int mouse_y=0;
    engine_interface.get_mouse_state(&mouse_x,&mouse_y);

    if(in_progress){
        if(engine_interface.game_command_state("scoreboard")){
            display_scoreboard=true;
        }

        //Handle camera directional keys being pressed.
        if(engine_interface.game_command_state("left")){
            cam_state="left";
        }
        if(engine_interface.game_command_state("up")){
            cam_state="up";
        }
        if(engine_interface.game_command_state("right")){
            cam_state="right";
        }
        if(engine_interface.game_command_state("down")){
            cam_state="down";
        }

        //Handle multiple camera directional keys being pressed at once.
        if(engine_interface.game_command_state("left") && engine_interface.game_command_state("up")){
            cam_state="left_up";
        }
        if(engine_interface.game_command_state("up") && engine_interface.game_command_state("right")){
            cam_state="right_up";
        }
        if(engine_interface.game_command_state("right") && engine_interface.game_command_state("down")){
            cam_state="right_down";
        }
        if(engine_interface.game_command_state("down") && engine_interface.game_command_state("left")){
            cam_state="left_down";
        }
        if(engine_interface.game_command_state("left") && engine_interface.game_command_state("right")){
            cam_state="left";
        }
        if(engine_interface.game_command_state("up") && engine_interface.game_command_state("down")){
            cam_state="up";
        }
        if(engine_interface.game_command_state("left") && engine_interface.game_command_state("up") && engine_interface.game_command_state("right")){
            cam_state="left_up";
        }
        if(engine_interface.game_command_state("left") && engine_interface.game_command_state("down") && engine_interface.game_command_state("right")){
            cam_state="left_down";
        }
        if(engine_interface.game_command_state("left") && engine_interface.game_command_state("up") && engine_interface.game_command_state("down")){
            cam_state="left_up";
        }
        if(engine_interface.game_command_state("up") && engine_interface.game_command_state("right") && engine_interface.game_command_state("down")){
            cam_state="right_up";
        }
        if(engine_interface.game_command_state("left") && engine_interface.game_command_state("up") && engine_interface.game_command_state("right") && engine_interface.game_command_state("down")){
            cam_state="left_up";
        }

        //If no camera directional keys are pressed, stop the camera.
        if(!engine_interface.game_command_state("left") && !engine_interface.game_command_state("up") && !engine_interface.game_command_state("right") && !engine_interface.game_command_state("down")){
            cam_state="none";
        }

        if(cam_state!="none"){
            game.world.selected_particle=-1;
        }
    }
}

void Game::handle_input_states(){
    int mouse_x=0;
    int mouse_y=0;
    engine_interface.get_mouse_state(&mouse_x,&mouse_y);

    if(in_progress){
        if(!paused){
            //Example multiplayer command state
            /**if(engine_interface.game_command_state("some_command")){
                command_states.push_back("some_command");
            }*/
        }
    }
}

bool Game::handle_game_command_gui(string command_name){
    //Pause the game.
    if(command_name=="pause"){
        toggle_pause();

        return true;
    }
    else if(command_name=="zoom_in"){
        zoom_camera_in(camera);

        return true;
    }
    else if(command_name=="zoom_out"){
        zoom_camera_out(camera);

        return true;
    }
    else if(command_name=="toggle_record"){
        recording=!recording;

        if(recording){
            record_frame=0;
        }

        return true;
    }
    else if(command_name=="toggle_show_particle_data"){
        show_particle_data=!show_particle_data;

        return true;
    }

    //Example multiplayer pause
    /**if(command_name=="pause"){
        if(network.status=="server"){
            toggle_pause();

            network.send_paused();
        }

        return true;
    }*/

    //Toggle chat box
    else if(command_name=="chat"){
        engine_interface.chat.toggle_on();

        return true;
    }

    return false;
}

bool Game::handle_game_command(string command_name){
    const uint8_t* keystates=SDL_GetKeyboardState(NULL);

    ///DEV COMMANDS
    if(engine_interface.option_dev && keystates[SDL_SCANCODE_F1]){
        //Example dev command
        /**if(command_name=="some_dev_command"){
            ///Dev command here.

            return true;
        }*/
    }
    ///END OF DEV COMMANDS

    if(!paused){
        //Example command
        /**if(command_name=="some_command"){
            ///Command here

            return true;
        }*/

        //Example multiplayer command input
        /**if(command_name=="some_command"){
            network.add_command(command_name);

            return true;
        }*/
    }

    return false;
}

bool Game::handle_input_events_gui(){
    bool event_consumed=false;

    if(in_progress){
        for(int i=0;i<engine_interface.game_commands.size() && !event_consumed;i++){
            if((event.type==SDL_CONTROLLERBUTTONDOWN && engine_interface.game_commands[i].button==event.cbutton.button) ||
               (event.type==SDL_KEYDOWN && event.key.repeat==0 && engine_interface.game_commands[i].key==event.key.keysym.scancode)){
                event_consumed=handle_game_command_gui(engine_interface.game_commands[i].name);
            }
        }

        if(!engine_interface.touch_controls && event.type==SDL_FINGERMOTION){
            if(!event_consumed){
                touch_events.push_back(event.tfinger);

                event_consumed=true;
            }
        }
    }

    return event_consumed;
}

bool Game::handle_input_events(){
    bool event_consumed=false;

    if(in_progress){
        int mouse_x=0;
        int mouse_y=0;
        engine_interface.get_mouse_state(&mouse_x,&mouse_y);

        for(int i=0;i<engine_interface.game_commands.size() && !event_consumed;i++){
            if((event.type==SDL_CONTROLLERBUTTONDOWN && engine_interface.game_commands[i].button==event.cbutton.button) ||
               (event.type==SDL_KEYDOWN && event.key.repeat==0 && engine_interface.game_commands[i].key==event.key.keysym.scancode)){
                event_consumed=handle_game_command(engine_interface.game_commands[i].name);
            }
        }

        if(event.type==SDL_MOUSEWHEEL){
            if(!event_consumed && event.wheel.y>0){
                zoom_camera_in(camera);

                event_consumed=true;
            }
            else if(!event_consumed && event.wheel.y<0){
                zoom_camera_out(camera);

                event_consumed=true;
            }
        }
        else if(event.type==SDL_MOUSEBUTTONDOWN){
            double x=(game.camera.x+(double)mouse_x)/game.camera_zoom;
            double y=(game.camera.y+(double)mouse_y)/game.camera_zoom;

            if(!event_consumed && event.button.button==SDL_BUTTON_LEFT){
                ///game.world.particles.push_back(Particle(SUPERMASSIVE_BLACK_HOLE_MASS,SUPERMASSIVE_BLACK_HOLE_DENSITY,x,y,Vector(0.0,0.0)));

                game.world.selected_particle=-1;

                Collision_Circ mouse(x,y,32.0/game.camera_zoom);
                for(int i=0;i<game.world.particles.size();i++){
                    if(collision_check_circ(mouse,game.world.particles[i].circle)){
                        game.world.selected_particle=i;
                        break;
                    }
                }

                event_consumed=true;
            }
            else if(!event_consumed && event.button.button==SDL_BUTTON_RIGHT){
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

                game.world.particles.push_back(Particle(mass_sagittarius_a_star,density_sagittarius_a_star,x,y,Vector(0.0,0.0)));

                game.world.particles.push_back(Particle(mass_sun,density_sun,x+distance_sun,y,Vector(velocity_sun,90.0)));

                game.world.particles.push_back(Particle(mass_mercury,density_mercury,x+distance_sun+distance_mercury,y,Vector(velocity_sun+velocity_mercury,90.0)));
                game.world.particles.push_back(Particle(mass_venus,density_venus,x+distance_sun+distance_venus,y,Vector(velocity_sun+velocity_venus,90.0)));
                game.world.particles.push_back(Particle(mass_earth,density_earth,x+distance_sun+distance_earth,y,Vector(velocity_sun+velocity_earth,90.0)));
                game.world.particles.push_back(Particle(mass_mars,density_mars,x+distance_sun+distance_mars,y,Vector(velocity_sun+velocity_mars,90.0)));
                game.world.particles.push_back(Particle(mass_jupiter,density_jupiter,x+distance_sun+distance_jupiter,y,Vector(velocity_sun+velocity_jupiter,90.0)));
                game.world.particles.push_back(Particle(mass_saturn,density_saturn,x+distance_sun+distance_saturn,y,Vector(velocity_sun+velocity_saturn,90.0)));
                game.world.particles.push_back(Particle(mass_uranus,density_uranus,x+distance_sun+distance_uranus,y,Vector(velocity_sun+velocity_uranus,90.0)));
                game.world.particles.push_back(Particle(mass_neptune,density_neptune,x+distance_sun+distance_neptune,y,Vector(velocity_sun+velocity_neptune,90.0)));
                game.world.particles.push_back(Particle(mass_pluto,density_pluto,x+distance_sun+distance_pluto,y,Vector(velocity_sun+velocity_pluto,90.0)));

                game.world.particles.push_back(Particle(mass_moon,density_moon,x+distance_sun+distance_earth+distance_moon,y,Vector(velocity_sun+velocity_earth+velocity_moon,90.0)));

                game.world.particles.push_back(Particle(mass_phobos,density_phobos,x+distance_sun+distance_mars+distance_phobos,y,Vector(velocity_sun+velocity_mars+velocity_phobos,90.0)));
                game.world.particles.push_back(Particle(mass_deimos,density_deimos,x+distance_sun+distance_mars+distance_deimos,y,Vector(velocity_sun+velocity_mars+velocity_deimos,90.0)));

                event_consumed=true;
            }
            else if(!event_consumed && event.button.button==SDL_BUTTON_MIDDLE){
                ///game.world.particles.push_back(Particle(MOON_MASS,MOON_DENSITY,x,y,Vector(0.0,0.0)));
                game.world.particles.push_back(Particle(SUPERMASSIVE_BLACK_HOLE_MASS*100000000000000000.0,SUPERMASSIVE_BLACK_HOLE_DENSITY*100000000000000000.0,x,y,Vector(0.0,0.0)));

                event_consumed=true;
            }
        }
    }

    return event_consumed;
}

void Game::handle_touch_events(){
    if(in_progress){
        if(touch_events.size()>=2){
            double touch_motion_threshold=0.005;

            if((abs(touch_events[0].dx)>touch_motion_threshold && abs(touch_events[1].dx)>touch_motion_threshold && touch_events[0].dx<0.0 && touch_events[1].dx>0.0) ||
            (abs(touch_events[0].dy)>touch_motion_threshold && abs(touch_events[1].dy)>touch_motion_threshold && touch_events[0].dy<0.0 && touch_events[1].dy>0.0)){
                zoom_camera_in(camera);
            }
            else if((abs(touch_events[0].dx)>touch_motion_threshold && abs(touch_events[1].dx)>touch_motion_threshold && touch_events[0].dx>0.0 && touch_events[1].dx<0.0) ||
            (abs(touch_events[0].dy)>touch_motion_threshold && abs(touch_events[1].dy)>touch_motion_threshold && touch_events[0].dy>0.0 && touch_events[1].dy<0.0)){
                zoom_camera_out(camera);
            }
        }
        else if(touch_events.size()==1){
            double touch_motion_threshold=0.005;

            if(abs(touch_events[0].dx)>touch_motion_threshold && abs(touch_events[0].dy)>touch_motion_threshold && touch_events[0].dx<0.0 && touch_events[0].dy<0.0){
                cam_state="left_up";
            }
            else if(abs(touch_events[0].dx)>touch_motion_threshold && abs(touch_events[0].dy)>touch_motion_threshold && touch_events[0].dx<0.0 && touch_events[0].dy>0.0){
                cam_state="left_down";
            }
            else if(abs(touch_events[0].dx)>touch_motion_threshold && touch_events[0].dx<0.0){
                cam_state="left";
            }
            else if(abs(touch_events[0].dx)>touch_motion_threshold && abs(touch_events[0].dy)>touch_motion_threshold && touch_events[0].dx>0.0 && touch_events[0].dy<0.0){
                cam_state="right_up";
            }
            else if(abs(touch_events[0].dx)>touch_motion_threshold && abs(touch_events[0].dy)>touch_motion_threshold && touch_events[0].dx>0.0 && touch_events[0].dy>0.0){
                cam_state="right_down";
            }
            else if(abs(touch_events[0].dx)>touch_motion_threshold && touch_events[0].dx>0.0){
                cam_state="right";
            }
            else if(abs(touch_events[0].dy)>touch_motion_threshold && touch_events[0].dy<0.0){
                cam_state="up";
            }
            else if(abs(touch_events[0].dy)>touch_motion_threshold && touch_events[0].dy>0.0){
                cam_state="down";
            }
            else{
                cam_state="none";
            }

            if(cam_state!="none"){
                game.world.selected_particle=-1;
            }
        }
    }
}

#include "game.h"
#include "world.h"
#include "render.h"

#include <SDL_image.h>

using namespace std;

Game::Game(){
    option_effect_limit=0;
    option_camera_speed=0.0;
    option_camera_zoom=0.0;
    option_name="";
    option_chat_timestamps=false;
    option_max_players=0;
    option_screen_shake=false;
    option_rumble=false;
    option_screensaver=false;

    option_record_length=false;

    display_scoreboard=false;

    in_progress=false;

    reset();
}

void Game::reset(){
    paused=false;

    cam_state="none";

    command_states.clear();

    camera.x=0.0;
    camera.y=0.0;

    reset_camera_dimensions();

    camera_delta_x=0.0;
    camera_delta_y=0.0;

    camera_speed=option_camera_speed;
    camera_zoom=option_camera_zoom;

    current_music="";

    recording=false;
    record_frame=0;
    show_particle_data=false;
}

void Game::reset_camera_dimensions(){
    camera.w=main_window.SCREEN_WIDTH;
    camera.h=main_window.SCREEN_HEIGHT;
}

string Game::get_random_direction_cardinal(){
    int random=rng.random_range(0,3);
    if(random==0){
        return "left";
    }
    else if(random==1){
        return "up";
    }
    else if(random==2){
        return "right";
    }
    else if(random==3){
        return "down";
    }
}

string Game::get_random_direction_cardinal_ordinal(){
    int random=rng.random_range(0,7);
    if(random==0){
        return "left";
    }
    else if(random==1){
        return "up";
    }
    else if(random==2){
        return "right";
    }
    else if(random==3){
        return "down";
    }
    else if(random==4){
        return "left_up";
    }
    else if(random==5){
        return "right_up";
    }
    else if(random==6){
        return "left_down";
    }
    else if(random==7){
        return "right_down";
    }
}

bool Game::effect_allowed(){
    uint32_t effects=/**world.effects_example.size()*/0;

    if(effects<option_effect_limit){
        return true;
    }
    else{
        return false;
    }
}

void Game::manage_music(){
    string music_to_play="";

    /**if(in_progress){
        music_to_play="1";
    }
    else{
        music_to_play="";
    }*/

    if(music_to_play.length()>0){
        if(music_to_play!=current_music){
            music.restart_track(music_to_play);
        }

        music.play_track(music_to_play);
    }
    else{
        music.stop_track();
    }

    current_music=music_to_play;
}

void Game::toggle_pause(){
    paused=!paused;

    sound_system.play_sound("pause");
}

void Game::start(){
    if(!in_progress){
        in_progress=true;

        reset();

        world.generate_world();
    }
}

void Game::start_client(){
    if(!in_progress){
        in_progress=true;

        reset();

        world.clear_world();
    }
}

void Game::stop(){
    network.stop();

    if(in_progress){
        in_progress=false;

        reset();

        world.clear_world();

        if(engine_interface.chat.on){
            engine_interface.chat.toggle_on();
        }
    }
}

void Game::center_camera(Collision_Rect box){
    camera.x=box.center_x()*camera_zoom-camera.w/2.0;
    camera.y=box.center_y()*camera_zoom-camera.h/2.0;
}

void Game::center_camera(Collision_Circ circle){
    camera.x=circle.x*camera_zoom-camera.w/2.0;
    camera.y=circle.y*camera_zoom-camera.h/2.0;
}

void Game::zoom_camera_in(Collision_Rect box){
    if(camera_zoom<ZOOM_MAX){
        Collision_Rect camera_location=box/camera_zoom;

        camera_zoom+=camera_zoom*ZOOM_RATE;
        if(camera_zoom>ZOOM_MAX){
            camera_zoom=ZOOM_MAX;
        }

        center_camera(camera_location);
    }
}

void Game::zoom_camera_in(Collision_Circ circle){
    if(camera_zoom<ZOOM_MAX){
        Collision_Circ camera_location=circle/camera_zoom;

        camera_zoom+=camera_zoom*ZOOM_RATE;
        if(camera_zoom>ZOOM_MAX){
            camera_zoom=ZOOM_MAX;
        }

        center_camera(camera_location);
    }
}

void Game::zoom_camera_out(Collision_Rect box){
    if(camera_zoom>ZOOM_MIN){
        Collision_Rect camera_location=box/camera_zoom;

        camera_zoom-=camera_zoom*ZOOM_RATE;
        if(camera_zoom<ZOOM_MIN){
            camera_zoom=ZOOM_MIN;
        }

        center_camera(camera_location);
    }
}

void Game::zoom_camera_out(Collision_Circ circle){
    if(camera_zoom>ZOOM_MIN){
        Collision_Circ camera_location=circle/camera_zoom;

        camera_zoom-=camera_zoom*ZOOM_RATE;
        if(camera_zoom<ZOOM_MIN){
            camera_zoom=ZOOM_MIN;
        }

        center_camera(camera_location);
    }
}

void Game::set_camera(){
    camera_delta_x=camera.x;
    camera_delta_y=camera.y;

    if(screen_shake.is_active()){
        camera.x-=(int64_t)screen_shake.x;
        camera.y-=(int64_t)screen_shake.y;

        screen_shake.movement();
    }

    if(game.world.selected_particle!=-1){
        center_camera(game.world.particles[game.world.selected_particle].circle);
    }
    else{
        if(cam_state=="left"){
            camera.x-=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="up"){
            camera.y-=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="right"){
            camera.x+=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="down"){
            camera.y+=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="left_up"){
            camera.x-=camera_speed/UPDATE_RATE;
            camera.y-=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="right_up"){
            camera.x+=camera_speed/UPDATE_RATE;
            camera.y-=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="right_down"){
            camera.x+=camera_speed/UPDATE_RATE;
            camera.y+=camera_speed/UPDATE_RATE;
        }
        else if(cam_state=="left_down"){
            camera.x-=camera_speed/UPDATE_RATE;
            camera.y+=camera_speed/UPDATE_RATE;
        }
    }

    if(screen_shake.is_active()){
        camera.x+=(int64_t)screen_shake.x;
        camera.y+=(int64_t)screen_shake.y;
    }

    camera_delta_x=camera.x-camera_delta_x;
    camera_delta_y=camera.y-camera_delta_y;
}

void Game::render_scoreboard(){
    if(display_scoreboard){
        Bitmap_Font* font=engine_interface.get_font("small");

        string name_list=network.get_name_list();
        string ping_list=network.get_ping_list();

        render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,0.5,"ui_black");

        font->show(72,(main_window.SCREEN_HEIGHT-(Strings::newline_count(name_list)+1)*font->spacing_y)/2.0,name_list,"ui_white");
        font->show(168,(main_window.SCREEN_HEIGHT-(Strings::newline_count(ping_list)+1)*font->spacing_y)/2.0,ping_list,"ui_white");
    }
}

void Game::record(){
    ///Note that changing logical framerate or resolution while recording could cause... problems...

    if(recording){
        #ifdef GAME_OS_ANDROID
            Log::add_error("Sorry, recording is disabled in Android, due to it exploding.");

            recording=false;
            return;
        #endif

        if((double)record_frame/UPDATE_RATE>(double)option_record_length){
            recording=false;
            return;
        }

        uint32_t total_frames=option_record_length*UPDATE_RATE;
        uint32_t total_digits=0;
        do{
            total_frames/=10;
            total_digits++;
        }while(total_frames!=0);

        uint32_t current_frame=record_frame;
        uint32_t frame_digits=0;
        do{
            current_frame/=10;
            frame_digits++;
        }while(current_frame!=0);

        uint32_t leading_zeroes_count=total_digits-frame_digits;
        string leading_zeroes="";
        for(int i=0;i<leading_zeroes_count;i++){
            leading_zeroes+=Strings::num_to_string(0);
        }

        string frame_name=engine_interface.get_save_directory()+"screenshots/";
        frame_name+=leading_zeroes+Strings::num_to_string(record_frame);
        frame_name+=".png";

        rtt_manager.record.make_render_target();

        world.render_background();

        world.render();

        int actual_width=rtt_manager.record.w;
        int actual_height=rtt_manager.record.h;

        unsigned char* pixel_data=(unsigned char*)malloc(4*actual_width*actual_height);

        if(pixel_data!=0){
            if(SDL_RenderReadPixels(main_window.renderer,NULL,SDL_PIXELFORMAT_ABGR8888,pixel_data,actual_width*4)!=0){
                string msg="Error reading renderer pixels: ";
                msg+=SDL_GetError();
                Log::add_error(msg);
            }

            uint32_t rmask,gmask,bmask,amask;
            engine_interface.get_rgba_masks(&rmask,&gmask,&bmask,&amask);

            SDL_Surface* surface=SDL_CreateRGBSurfaceFrom(pixel_data,actual_width,actual_height,32,actual_width*4,rmask,gmask,bmask,amask);

            if(surface==0){
                string msg="Error creating surface for record: ";
                msg+=SDL_GetError();
                Log::add_error(msg);
            }
            else{
                SDL_Surface* surface_final=SDL_CreateRGBSurface(0,actual_width,actual_height,32,rmask,gmask,bmask,amask);

                if(surface_final==0){
                    string msg="Error creating final surface for record: ";
                    msg+=SDL_GetError();
                    Log::add_error(msg);
                }
                else{
                    if(SDL_MUSTLOCK(surface)){
                        SDL_LockSurface(surface);
                    }
                    if(SDL_MUSTLOCK(surface_final)){
                        SDL_LockSurface(surface_final);
                    }

                    for(int x=0;x<actual_width;x++){
                        for(int y=0;y<actual_height;y++){
                            Color color=surface_get_pixel(surface,x,y);

                            surface_put_pixel(surface_final,x,actual_height-1-y,color);
                        }
                    }

                    if(SDL_MUSTLOCK(surface)){
                        SDL_UnlockSurface(surface);
                    }
                    if(SDL_MUSTLOCK(surface_final)){
                        SDL_UnlockSurface(surface_final);
                    }

                    if(IMG_SavePNG(surface_final,frame_name.c_str())!=0){
                        string msg="Error saving screenshot: ";
                        msg+=IMG_GetError();
                        Log::add_error(msg);
                    }

                    SDL_FreeSurface(surface_final);
                }

                SDL_FreeSurface(surface);
            }

            free(pixel_data);
        }
        else{
            Log::add_error("Error allocating memory for screenshot.");
        }

        rtt_manager.record.reset_render_target();

        record_frame++;
    }
}

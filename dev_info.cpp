/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "engine_interface.h"
#include "world.h"
#include "render.h"

using namespace std;

void Engine_Interface::render_dev_info(){
    string msg="";

    if(game.in_progress){
        msg+="Camera Position: "+Strings::num_to_string(game.camera.x*game.camera_zoom)+","+Strings::num_to_string(game.camera.y*game.camera_zoom)+"\n";
        msg+="Camera Size: "+Strings::num_to_string(game.camera.w/game.camera_zoom)+","+Strings::num_to_string(game.camera.h/game.camera_zoom)+"\n";
        msg+="Camera Zoom: "+Strings::num_to_string(game.camera_zoom)+"\n";

        /**msg+="\n";
        msg+="Universe mass: "+Strings::num_to_string(game.world.universe_mass)+" kg"+"\n";
        msg+="Universe density: "+Strings::num_to_string(game.world.universe_density)+" kg/km^3"+"\n";*/
        ///msg+="Universe volume: "+Strings::num_to_string(game.world.universe_volume)+" km^3"+"\n";

        msg+="\n";
        msg+="Objects: "+Strings::num_to_string(game.world.particles.size())+"\n";

        msg+="\n";
        msg+="Time: "+Strings::time_string((int)ceil(TIME_SCALE))+" per second"+"\n";
    }

    if(msg.length()>0){
        Bitmap_Font* font=engine_interface.get_font("small");

        render_rectangle(2.0,2.0,Strings::longest_line(msg)*font->spacing_x,Strings::newline_count(msg)*font->spacing_y,0.75,"ui_black");
        font->show(2.0,2.0,msg,"red");
    }
}

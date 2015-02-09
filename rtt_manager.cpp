#include "rtt_manager.h"
#include "world.h"

using namespace std;

void Rtt_Manager::create_textures(){
    record.create_texture(game.camera.w,game.camera.h);
}

void Rtt_Manager::unload_textures(){
    record.unload_texture();
}

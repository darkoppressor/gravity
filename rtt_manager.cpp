/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "rtt_manager.h"
#include "world.h"

using namespace std;

void Rtt_Manager::create_textures(){
    record.create_texture(game.camera.w,game.camera.h);
}

void Rtt_Manager::unload_textures(){
    record.unload_texture();
}

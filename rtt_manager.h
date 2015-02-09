#ifndef rtt_manager_h
#define rtt_manager_h

#include "rtt_data.h"

class Rtt_Manager{
public:

    Rtt_Data record;

    void create_textures();
    void unload_textures();
};

#endif

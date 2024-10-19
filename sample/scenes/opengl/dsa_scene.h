#pragma once

#include "core/typedef.h"
#include "system/scene.h"


namespace emt
{
    
    class dsa_scene : public scene
    {
    public:
        dsa_scene() = default;

        void init_frame();
        void update_frame(float dt);
        void render_frame();
        void release_frame();
        /* data */

        
    };
    
    
} // namespace emt

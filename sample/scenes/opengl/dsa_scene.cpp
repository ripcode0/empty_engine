#include "dsa_scene.h"
#include "graphics/graphics.h"
#include "graphics/context.h"
#include "graphics/opengl/gl_config.h"
#include "scenes/opengl/debug_object.h"
#include "graphics/buffer.h"
#include "graphics/opengl/gl_buffer.h"

namespace emt
{
    void dsa_scene::init_frame()
    {
        

        float vertices[9] = {
            1,1,1,1,1,1,1,1,1
        };
        
        
    }

    void dsa_scene::update_frame(float dt)
    {
    }

    void dsa_scene::render_frame()
    {
        context::clear(0.5f, 0.2f, 0.3f, 1.f);  
        


        context::swap_buffers();        
    }

    void dsa_scene::release_frame()
    {
    }

} // namespace emt



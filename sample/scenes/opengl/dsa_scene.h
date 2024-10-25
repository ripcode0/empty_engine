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

        uint cmd_buffer{};

        struct draw_command
        {
            GLenum mode;
            GLint first;
            GLsizei count;
        };
        
        uint index_buffer{};
        uint vbo{};
        uint vao{};
        
        vertex_shader* m_vs;
        pixel_shader* m_ps;
        uint m_pipeline;

        uint64 vbo_addr;
        uint64 ibo_addr;

        struct
        {
            uint id;
            uint64 addr;
        }obj[3];


        uint state;
        uint cmdlist;
        
        
        
    };
    
    
} // namespace emt

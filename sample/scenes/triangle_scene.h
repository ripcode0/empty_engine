#pragma once

#include "system/scene.h"
#include "core/typedef.h"

namespace emt
{
    class basic_scene : public scene
    {
    public:
        basic_scene() = default;

        void init_frame() override;
        void update_frame(float dt) override;
        void render_frame() override;
        void release_frame() override;

        //ibuffer* m_vbo{};
        vertex_buffer* m_vbo;
        ibuffer* m_ibo{};
        input_layout* m_input_layout{};
        vertex_shader* m_vs;
        //shader* m_ps;
        

        vertex_shader* vbs;
        pixel_shader* m_ps;
        geometry_shader* m_gs;
        
        uint m_qr;

        uniform_buffer* m_ubo{};

        camera* m_camera{};

        struct graphics_commad_list
        {
            void set_vertex_buffer(uint id){

            }
        };

    };    
} // namespace emt


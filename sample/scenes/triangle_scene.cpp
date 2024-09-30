#include "triangle_scene.h"
#include "graphics/context.h"
#include "graphics/graphics.h"

namespace emt
{
    void emt::triangle_scene::init_frame()
    {
        vertex_pc vertices[] = {
            {{0.f,0.f,0.f},{1.f, 0.f, 0.f}},
            {{0.f,0.f,0.f},{1.f, 0.f, 0.f}},
            {{0.f,0.f,0.f},{1.f, 0.f, 0.f}}
        };

        buffer_create_info buffer_info{};
        buffer_info.p_data = vertices;
        buffer_info.size = _countof(vertices) * sizeof(vertex_pc);
        buffer_info.type = bufffer_type::vertex;
    
        graphics::create_vertex_buffer(buffer_info, &m_vbo);

        uint indices[] = { 0,1,2};

        buffer_info.p_data = indices;
        buffer_info.size = sizeof(uint) * _countof(indices);
        buffer_info.type = bufffer_type::index;

        graphics::create_vertex_buffer(buffer_info, &m_ibo);

        vertex_attrib attr[] = {
            {0, vertex_format_float, 3, sizeof(vertex_pc), 0},
            {0, vertex_format_float, 3, sizeof(vertex_pc), offsetof(vertex_pc, vertex_pc::color)}
        };

        input_layout_create_info input_info{};
        input_info.p_attrib = attr;
        input_info.attr_size = _countof(attr);

        graphics::create_input_layout(input_info, &m_input_layout);
        
    }
    void triangle_scene::update_frame(float dt)
    {
    }
    void triangle_scene::render_frame()
    {
        graphics_context::clear(0.3f,0.4f,0.5f,1.f);

        vertex_buffer* vertex_buffers[] = {(vertex_buffer*)m_vbo};
        uint offset = 0;
        uint stride = sizeof(vertex_pc);
        
        graphics_context::set_vertex_buffer(0, 1, vertex_buffers, &offset, &stride);


        graphics_context::swap_buffers();
    }
    void triangle_scene::release_frame()
    {
    }
} // namespace emt

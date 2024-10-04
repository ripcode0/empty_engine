#include "triangle_scene.h"
#include "graphics/context.h"
#include "graphics/graphics.h"

namespace emt
{
    void emt::triangle_scene::init_frame()
    {
        vertex_pc vertices[] = {
            {{-0.5f,-0.5f,0.f},{1.f, 0.f, 0.f}},
            {{ 0.0f, 0.5f,0.f},{1.f, 0.f, 0.f}},
            {{ 0.5f,-0.5f,0.f},{1.f, 0.f, 0.f}}
        };

        buffer_create_info buffer_info{};
        buffer_info.p_data = vertices;
        buffer_info.size = _countof(vertices) * sizeof(vertex_pc);
        buffer_info.type = bufffer_type::vertex;
    
        graphics::create_buffer(buffer_info, &m_vbo);

        uint indices[] = { 0,1,2};

        buffer_info.p_data = indices;
        buffer_info.size = sizeof(uint) * _countof(indices);
        buffer_info.type = bufffer_type::index;

        graphics::create_buffer(buffer_info, &m_ibo);

        vertex_attrib attr[] = {
            {0, vertex_format_float, 3, sizeof(vertex_pc), 0},
            {1, vertex_format_float, 3, sizeof(vertex_pc), offsetof(vertex_pc, vertex_pc::color)}
        };

        input_layout_create_info input_info{};
        input_info.p_attrib = attr;
        input_info.attr_size = _countof(attr);

        graphics::create_input_layout(input_info, &m_input_layout);
     

        graphics::create_shader("test_vs", shader_type::vertex, &m_vs);
        graphics::create_shader("test_ps", shader_type::pixel, &m_ps);

        context::set_vertex_shader(m_vs);
        context::set_pixel_shader(m_ps);

        context::set_input_layout(m_input_layout);

        
        uint offset = 0;
        uint stride = sizeof(vertex_pc);
        vertex_buffer* vbo = (vertex_buffer*)m_vbo;
        context::set_vertex_buffer(0, 1, &vbo, &offset, &stride);
        context::set_index_buffer(m_ibo, vertex_format::vertex_format_byte);
        
    }
    void triangle_scene::update_frame(float dt)
    {
    }
    void triangle_scene::render_frame()
    {
        context::clear(0.3f,0.4f,0.5f,1.f);

        // vertex_buffer* vertex_buffers[] = {(vertex_buffer*)m_vbo};
        // uint offset = 0;
        // uint stride = sizeof(vertex_pc);
        
        // graphics_context::set_vertex_buffer(0, 1, vertex_buffers, &offset, &stride);

        context::draw_indexed(3,0);

        context::swap_buffers();
    }
    void triangle_scene::release_frame()
    {
    }
} // namespace emt

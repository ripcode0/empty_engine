#include "triangle_scene.h"
#include "graphics/context.h"
#include "graphics/graphics.h"
#include "graphics/opengl/gl_config.h"
#include "graphics/buffer.h"
#include "component/camera.h"

namespace emt
{
    void emt::basic_scene::init_frame()
    {
        viewport vp{};
        
        //m_camera = new camera()        

        vertex_pc vertices[] = {
            {{-0.5f,-0.5f,0.f},{1.f, 0.f, 0.f}},
            {{ 0.0f, 0.5f,0.f},{1.f, 0.f, 0.f}},
            {{ 0.5f,-0.5f,0.f},{1.f, 0.f, 0.f}}
        };

        buffer_create_info buffer_info{};
        buffer_info.p_data = vertices;
        
        buffer_info.size = _countof(vertices) * sizeof(vertex_pc);
        buffer_info.type = buffer_type::vertex;

        //graphics::create_buffer(buffer_info, &m_vbo);
        graphics::create_vertex_buffer(buffer_info, &m_vbo);

        uint indices[] = { 0,1,2};
        
        buffer_info = {};
        buffer_info.p_data = indices;
        buffer_info.size = sizeof(uint) * _countof(indices);
        buffer_info.type = buffer_type::index;

        graphics::create_buffer(buffer_info, &m_ibo);

        vertex_attrib attr[] = {
            {0, vertex_format_float, 3, sizeof(vertex_pc), 0,0},
            {1, vertex_format_float, 3, sizeof(vertex_pc), offsetof(vertex_pc, vertex_pc::color), 0}
        };

        input_layout_create_info input_info{};
        input_info.p_attrib = attr;
        input_info.attr_size = _countof(attr);

        graphics::create_input_layout(input_info, &m_input_layout);
     
        
        graphics::create_vertex_shader("test_vs",&m_vs);
        //graphics::create_vertex_shader("instance_vs", &m_vs);
        graphics::create_pixel_shader("test_ps", &m_ps);
        graphics::create_geometry_shader("test_gs", &m_gs);
        
        
        context::set_vertex_shader(m_vs);

        context::set_pixel_shader(m_ps);

        context::set_input_layout(m_input_layout);

        context::clear_depth(0xffffff);

        buffer_info = {};
        buffer_info.size = sizeof(vec3f);
        vec3f color(1.f,0.5f, 0.3f);
        buffer_info.p_data = &color;
        buffer_info.type = buffer_type::uniform;

        graphics::create_uniform_buffer(buffer_info, &m_ubo);

    }

    

    void basic_scene::update_frame(float dt)
    {



    }
    void basic_scene::render_frame()
    {
        context::clear(0.2f,0.2f,0.2f,1.f);

        context::set_input_layout(m_input_layout);

        uint stride = sizeof(vertex_pc);
        uint offset = 0;
        context::set_vertex_buffer(0, 1, &m_vbo, &offset, &stride);
        context::set_index_buffer(m_ibo, format::r32_uint);
        context::set_vertex_shader(m_vs);
        context::set_pixel_shader(m_ps);
        context::set_geometry_shader(m_gs);
        context::set_uniform_buffer(0, m_ubo);
        
        static uint64 frame = 0;
        frame++;
        float f = std::sinf((float)frame * 0.03f);
        vec3f color(1.f - f, 1.f-f, 0);
        
        m_ubo->sub_data(0, sizeof(vec3f), &color);

        context::draw_indexed(3, 0);

        context::set_geometry_shader(nullptr);
        context::draw_indexed(3, 0);

        context::swap_buffers();
    }
    void basic_scene::release_frame()
    {
        graphics::release_buffer(m_vbo);
        
    }
} // namespace emt

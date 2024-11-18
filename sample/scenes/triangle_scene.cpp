#include "triangle_scene.h"
#include "graphics/context.h"
#include "graphics/graphics.h"
#include "graphics/opengl/gl_config.h"
#include "graphics/buffer.h"
#include "component/camera.h"
#include "graphics/graphics_context.h"

namespace emt
{
    void emt::basic_scene::init_frame()
    {
        viewport vp{};

        
        
        context::get_viewport(&vp);

        float ratio = vp.width / vp.height;
        m_camera = new emt::camera(45.f, ratio, 0.001f, 1000.f);    
        m_camera->look_at({0.f,5.f,-5.f}, {0,0,0});    
        //m_camera->pos = {0.f, 0.f, -2.f};
        //m_camera->internal_update();
        

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
            {0, format::rgb32_float, sizeof(vertex_pc), 0,0},
            {1, format::rgb32_float, sizeof(vertex_pc), offsetof(vertex_pc, vertex_pc::color), 0}
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

        matrices.proj = m_camera->proj;
        matrices.view = m_camera->view;
        
        buffer_info = {};
        buffer_info.size = sizeof(mat4x4) * 2;
        buffer_info.p_data = &matrices;
        buffer_info.type = buffer_type::uniform;

        graphics::create_uniform_buffer(buffer_info, &m_ubo);

    }

    void basic_scene::update_frame(float dt)
    {
  
        m_camera->update_frame(dt);

        mat4x4 mat[2] = {m_camera->proj, m_camera->view};
        m_ubo->sub_data(0, sizeof(mat4x4) * 2, mat);


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
        //context::set_geometry_shader(m_gs);
        context::set_uniform_buffer(0, m_ubo);
        
        context::set_topology(topology::triangles);

        context::draw_indexed(3, 0);

        context::set_geometry_shader(nullptr);
        //context::draw_indexed(3, 0);

        context::swap_buffers();
    }
    void basic_scene::release_frame()
    {
        graphics::release_buffer(m_vbo);
        
    }
    void basic_scene::create_grid()
    {
        int slice = 3;
        int size = 3;

        std::vector<vertex_pc> vertices;

        for(int i = -size; i <= size; i++){
            float x = (float)i;
            float y = 0.f;
            //float z = 
        }
    }
} // namespace emt

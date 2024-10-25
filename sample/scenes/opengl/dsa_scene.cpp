#include "scenes/opengl/dsa_scene.h"
#include "graphics/graphics.h"
#include "graphics/context.h"
#include "graphics/opengl/gl_config.h"
#include "scenes/opengl/debug_object.h"
#include "graphics/buffer.h"
#include "graphics/opengl/gl_buffer.h"
#include "graphics/opengl/gl_shader.h"

namespace emt
{
    void dsa_scene::init_frame()
    {
        if(wglad::has_extension("GL_NV_vertex_buffer_unified_memory")){
            printf("%s\n","enable : GL_NV_vertex_buffer_unified_memory extension");
        }
        
        vertex_pc vertices[] = {
            {{-0.5f,-0.5f,0.f},{1.f, 0.f, 0.f}},
            {{ 0.0f, 0.5f,0.f},{1.f, 0.f, 0.f}},
            {{ 0.5f,-0.5f,0.f},{1.f, 0.f, 0.f}}
        };

        
        
        glCreateBuffers(1, &vbo);
        glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glMakeNamedBufferResidentNV(vbo, GL_READ_ONLY);
        glGetNamedBufferParameterui64vNV(vbo, GL_BUFFER_GPU_ADDRESS_NV, &vbo_addr);

        glCreateVertexArrays(1, &vao);
        glEnableVertexArrayAttrib(vao, 0);
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 0, 0);

        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 12);
        glVertexArrayAttribBinding(vao, 1, 0);
        

        glVertexArrayVertexBuffer(vao, 0, vbo, 0, 24);

        glBindVertexArray(vao);

        glCreateBuffers(1, &index_buffer);

        uint indices[] = {0, 1,2};
        glNamedBufferData(index_buffer, sizeof(indices), indices, GL_STATIC_DRAW);

        GLuint64 virtual_addr{};
        

        glMakeNamedBufferResidentNV(index_buffer, GL_READ_ONLY);
        glGetNamedBufferParameterui64vNV(index_buffer, GL_BUFFER_GPU_ADDRESS_NV, &ibo_addr);

        printf("vbo addr : %zu\n", ibo_addr);
        glBufferAddressRangeNV(GL_ELEMENT_ARRAY_ADDRESS_NV, 10, ibo_addr, sizeof(indices));

        
        glVertexArrayElementBuffer(vao, index_buffer);
        
        //glDrawArraysIndirect()

        glCreateProgramPipelines(1, &m_pipeline);

        glBindProgramPipeline(m_pipeline);

        m_vs = new gl_vertex_shader("data/shaders/glsl/test_vs.glsl");
        m_ps = new gl_pixel_shader("data/shaders/glsl/test_ps.glsl");
        gl_vertex_shader* vs = (gl_vertex_shader*)m_vs;
        gl_pixel_shader* ps = (gl_pixel_shader*)m_ps;
        glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vs->gpu_shader_id);
        glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, ps->gpu_shader_id);

        glCreateStatesNV(1, &state);

        glCreateCommandListsNV(1, &cmdlist);

        
        auto stage = glGetStageIndexNV(GL_VERTEX_SHADER);
        auto stag = glGetStageIndexNV(GL_FRAGMENT_SHADER);

        uint i = 0;

    }

    void dsa_scene::update_frame(float dt)
    {
    }

    void dsa_scene::render_frame()
    {
        context::clear(0.5f, 0.2f, 0.3f, 1.f);  
        //glVertexArrayElementBuffer(vao, index_buffer);
        
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glCompileCommandListNV(cmdlist);

        context::swap_buffers();        
    }

    void dsa_scene::release_frame()
    {
    }

} // namespace emt



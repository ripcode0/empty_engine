#include "gl_context.h"
#include "graphics/opengl/gl_config.h"
#include "graphics/opengl/gl_input_layout.h"
#include "graphics/opengl/gl_buffer.h"
#include "graphics/opengl/gl_shader.h"
#include "core/config.h"

namespace emt
{
    gl_context::gl_context(uint cx, uint cy, HWND hwnd, bool vsync)
        : context(cx, cy, hwnd, graphics_api::opengl, vsync)
    {
        wglad::create_context_from_hwnd(hwnd, &m_glrc, &m_dc);
        glCreateProgramPipelines(1, &m_shader_pipeline);
        glBindProgramPipeline(m_shader_pipeline);
    }

    gl_context::~gl_context()
    {
        glDeleteProgramPipelines(1, &m_shader_pipeline);
        wglad::release_context(m_hwnd, m_glrc, m_dc);
    }

    void gl_context::clear_t(float r, float g, float b, float a)
    {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void gl_context::set_input_layout_t(input_layout *layout)
    {
        m_vao = ((gl_input_layout*)layout)->m_vao;
        glBindVertexArray(m_vao);

        if(m_asm.buffers[0]){
            glVertexArrayVertexBuffers(
                m_vao,
                m_asm.slot,
                m_asm.count,
                m_asm.buffers,
                (GLintptr*)m_asm.offsets,
                m_asm.strides);
        }
        if(m_ibo){
            glVertexArrayElementBuffer(m_vao, m_ibo);
        }

    }

    void gl_context::set_vertex_buffer_t(uint slot, uint count, vertex_buffer *const *buffers, const uint *offset, const uint *strides)
    {
        m_asm.slot = slot;
        m_asm.count = count;
        for(uint i =0; i < count; ++i){
            m_asm.buffers[i] = reinterpret_cast<gl_vertex_buffer*>(buffers[i])->m_buffer;
            m_asm.offsets[i] = (int)offset[i];
            m_asm.strides[i] = (int)strides[i];
        }
        if(m_vao){
            glVertexArrayVertexBuffers(
                m_vao,
                m_asm.slot,
                m_asm.count,
                m_asm.buffers,
                (GLintptr*)m_asm.offsets,
                m_asm.strides);
        }
    }

    

    void gl_context::set_index_buffer_t(ibuffer *ibo, vertex_format format)
    {
        m_ibo = ((gl_index_buffer*)ibo)->m_buffer;
        if(m_vao){
            glVertexArrayElementBuffer(m_vao, m_ibo);
        }
    }

    void gl_context::set_vertex_shader_t(const shader *shader)
    {
        if(shader->type != shader_type::vertex){
            return;
        }
        uint vs = ((gl_shader*)shader)->program;
        glUseProgramStages(m_shader_pipeline, GL_VERTEX_SHADER_BIT, vs);
    }

    void gl_context::set_pixel_shader_t(const shader *shader)
    {
        if(shader->type != shader_type::pixel){       
            return;
        }
        uint ps = ((gl_shader*)shader)->program;
        glUseProgramStages(m_shader_pipeline, GL_FRAGMENT_SHADER_BIT, ps);
    }

    void gl_context::draw_indexed_t(uint count, uint offset)
    {
        #ifdef _DEBUG
        if(!m_asm.buffers[0] && !m_vao && !m_ibo){
            
        }
        #endif
        
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
    
    void gl_context::swap_buffers_t()
    {
        ::SwapBuffers(m_dc);
    }

} // namespace emt

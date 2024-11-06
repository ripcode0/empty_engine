#include "gl_context.h"
#include "graphics/opengl/gl_config.h"
#include "graphics/opengl/gl_input_layout.h"
#include "graphics/opengl/gl_buffer.h"
#include "graphics/opengl/gl_shader.h"
#include "core/config.h"
#include "graphics/graphics.h"

namespace emt
{
    gl_context::gl_context(uint cx, uint cy, HWND hwnd, bool vsync)
        : context(cx, cy, hwnd, graphics_api::opengl, vsync)
    {
        wglad::create_context_from_hwnd(hwnd, &m_glrc, &m_dc);
        glCreateProgramPipelines(1, &m_shader_pipeline);
        glBindProgramPipeline(m_shader_pipeline);
        wglSwapIntervalEXT(vsync ? 1 : 0);
        graphics::reserve_graphics_memories();
    }

    gl_context::~gl_context()
    {
        graphics::release_graphics_memories();

        glDeleteProgramPipelines(1, &m_shader_pipeline);
        wglad::release_context(m_hwnd, m_glrc, m_dc);
    }

    void gl_context::clear_t(float r, float g, float b, float a)
    {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT);
        
    }

    void gl_context::set_viewport_t(const viewport *vp)
    {
        float x = vp->x;
        float y = client_height - (vp->height + vp->y);
        float w = vp->width;
        float h = vp->height;
        
        glViewport(x, y, w, h);
        glDepthRange(vp->min_depth, vp->max_depth);
    }

    void gl_context::get_viewport_t(viewport *vp)
    {
        float* ptr = (float*)vp;
        GLfloat v[4];
        glGetFloatv(GL_VIEWPORT, v);
        GLfloat dr[2];
        glGetFloatv(GL_DEPTH_RANGE, dr);
        memcpy(ptr, v, sizeof(float) * 4);
        ptr += 4;
        memcpy(ptr, dr, sizeof(float) * 2);
    }

    void gl_context::set_scissor_t(const rect &rc)
    {
        uint inverse_y = client_height - (rc.y + rc.height);
        //glScissorIndexed(0, rc.x, inverse_y, rc.width, rc.height);
        glScissor(rc.x, inverse_y, rc.width, rc.height);
        glEnable(GL_SCISSOR_TEST);
    }

    void gl_context::set_input_layout_t(input_layout *layout)
    {
        m_vao = ((gl_input_layout*)layout)->vao;
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
            m_asm.buffers[i] = reinterpret_cast<gl_vertex_buffer*>(buffers[i])->handle;
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

    

    void gl_context::set_index_buffer_t(ibuffer *ibo, format format)
    {
        m_ibo = ((gl_index_buffer*)ibo)->handle;
        if(m_vao){
            glVertexArrayElementBuffer(m_vao, m_ibo);
        }
    }

    void gl_context::set_vertex_shader_t(const vertex_shader *shader)
    {
        uint vs = 0;
        if(shader){
            vs = ((gl_vertex_shader*)shader)->gpu_shader_id;
        }
        glUseProgramStages(m_shader_pipeline, GL_VERTEX_SHADER_BIT, vs);
    }

    void gl_context::set_pixel_shader_t(const pixel_shader *shader)
    {
        uint ps = 0;
        if(shader){
            ps = ((gl_pixel_shader*)shader)->gpu_shader_id;
        }
        glUseProgramStages(m_shader_pipeline, GL_FRAGMENT_SHADER_BIT, ps);
    }

    void gl_context::set_geometry_shader_t(const geometry_shader* shader)
    {
        uint gs = 0;
        if(shader){
            gs = ((gl_geometry_shader*)shader)->gpu_shader_id;
        }
        glUseProgramStages(m_shader_pipeline, GL_GEOMETRY_SHADER_BIT, gs);
    }

    void gl_context::draw_indexed_t(uint count, uint offset)
    {
        #ifdef _DEBUG
        if(!m_asm.buffers[0] && !m_vao && !m_ibo){
            
        }
        #endif
        
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void gl_context::set_uniform_buffer_t(uint index, uniform_buffer *buffer)
    {
        
        if(buffer){
            uint ubo = ((gl_uniform_buffer*)buffer)->handle;

            glBindBufferBase(GL_UNIFORM_BUFFER, index, ubo);
        }else{
            glBindBufferBase(GL_UNIFORM_BUFFER, index, NULL);
        }
    }

    void gl_context::swap_buffers_t()
    {
        ::SwapBuffers(m_dc);
    }

} // namespace emt

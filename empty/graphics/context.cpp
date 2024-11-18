#include "context.h"
#include "graphics/buffer.h"

namespace emt
{
    context::context(uint cx, uint cy, HWND hwnd, graphics_api api, bool vsync)
        : m_hwnd(hwnd), client_width(cx), client_height(cy)
    {
        this->api = api;
        if(!shared_context){
            shared_context = this;
        }
    }

    context::~context()
    {
        shared_context = nullptr;
    }

    void context::clear(float r, float g, float b, float a)
    {
        shared_context->clear_t(r, g, b, a);
    }

    void context::clear_depth(float value)
    {
        
    }

    void context::set_viewport(const viewport* vp)
    {
        shared_context->set_viewport_t(vp);
    }

    void context::get_viewport(viewport *vp)
    {
        shared_context->get_viewport_t(vp);
    }

    void context::set_scissor(const rect &rc)
    {
        shared_context->set_scissor_t(rc);
    }

    void context::set_input_layout(input_layout *layout)
    {
        shared_context->set_input_layout_t(layout);
    }

    void context::set_vertex_buffer(uint slot, uint count, vertex_buffer *const *buffers, const uint *offset, const uint *strides)
    {
        shared_context->set_vertex_buffer_t(slot, count, buffers, offset, strides);
    }

    void context::set_vertex_shader(const vertex_shader *shader)
    {
        shared_context->set_vertex_shader_t(shader);
    }

    void context::set_pixel_shader(const pixel_shader *shader)
    {
        shared_context->set_pixel_shader_t(shader);
    }

    void context::set_geometry_shader(const geometry_shader *shader)
    {
        shared_context->set_geometry_shader_t(shader);
    }

    void context::set_index_buffer(ibuffer *buffer, format format)
    {
        shared_context->set_index_buffer_t(buffer, format);
    }

    void context::draw_indexed(uint count, uint offset)
    {
        shared_context->draw_indexed_t(count, offset);
    }

    void context::set_uniform_buffer(uint index, uniform_buffer* buffer)
    {
        
        shared_context->set_uniform_buffer_t(index, buffer);
    }

    void context::set_topology(const topology &topology)
    {
        shared_context->set_topology_t(topology);
    }

    void context::swap_buffers()
    {
        shared_context->swap_buffers_t();
    }

} // namespace emt


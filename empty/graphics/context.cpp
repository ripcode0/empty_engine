#include "context.h"
#include "graphics/buffer.h"

namespace emt
{
    graphics_context::graphics_context(uint cx, uint cy, HWND hwnd, graphics_api api, bool vsync)
        : m_hwnd(hwnd)
    {
        this->api = api;
        if(!shared_context){
            shared_context = this;
        }
    }

    graphics_context::~graphics_context()
    {
        shared_context = nullptr;
    }

    void graphics_context::clear(float r, float g, float b, float a)
    {
        shared_context->clear_t(r, g, b, a);
    }

    void graphics_context::clear_depth(float value)
    {
        
    }

    void graphics_context::set_input_layout(input_layout *layout)
    {
        shared_context->set_input_layout_t(layout);
    }

    void graphics_context::set_vertex_buffer(uint slot, uint count, vertex_buffer *const *buffers, const uint *offset, const uint *strides)
    {
        shared_context->set_vertex_buffer_t(slot, count, buffers, offset, strides);
    }

    void graphics_context::set_index_buffer(ibuffer *buffer, vertex_format format)
    {
        shared_context->set_index_buffer_t(buffer, format);
    }

    void graphics_context::swap_buffers()
    {
        shared_context->swap_buffers_t();
    }

} // namespace emt


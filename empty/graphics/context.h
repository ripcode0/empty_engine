#pragma once

#include "core/typedef.h"

namespace emt{
    class graphics_context
    {
    public:
        graphics_context(uint cx, uint cy, HWND hwnd, graphics_api api, bool vsync);
        virtual ~graphics_context();

        static void clear(float r, float g, float b, float a);
        static void clear_depth(float value);
        static void set_input_layout(input_layout* layout);
        static void set_vertex_buffer(
            uint slot,
            uint count,
            vertex_buffer* const* buffers,
            const uint* offset,
            const uint* strides);
        
        static void set_index_buffer(ibuffer* buffer, vertex_format format);

        static void swap_buffers();

        HWND m_hwnd;
        inline static graphics_api api = graphics_api::opengl;  
    private:
        virtual void clear_t(float r, float g, float b, float a) = 0;
        
        virtual void set_input_layout_t(input_layout* layout) = 0;
        virtual void set_vertex_buffer_t(
            uint slot,
            uint count,
            vertex_buffer* const* buffers,
            const uint* offset,
            const uint* strides) = 0;
        virtual void set_index_buffer_t(ibuffer* buffer, vertex_format format) = 0;
        virtual void swap_buffers_t() = 0;

        inline static graphics_context* shared_context{};
        // inline static graphics_api api = graphics_api::opengl;  
        
    };
    
}
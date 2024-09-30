#pragma once

#include "graphics/context.h"

namespace emt
{
    #define  max_vertex_buffer_binding  32
    class gl_context : public graphics_context
    {
        public:
        gl_context(uint cx, uint cy, HWND hwnd, bool vsync);
        ~gl_context();
        
    private:
        void clear_t(float r, float g, float b, float a) override;
        void set_input_layout_t(input_layout* layout) override;

        void set_vertex_buffer_t(
            uint slot,
            uint count,
            vertex_buffer* const* buffers,
            const uint* offset,
            const uint* strides) override;

        virtual void set_index_buffer_t(ibuffer* buffer, vertex_format format) override;
        void draw_indexed_t(uint count);
        void swap_buffers_t() override;

        HGLRC m_glrc{};
        HDC m_dc{};


        struct gl_vertex_iasm
        {
            uint slot;
            uint count;
            uint buffers[max_vertex_buffer_binding];
            int offsets[max_vertex_buffer_binding];
            int strides[max_vertex_buffer_binding];
        };

        gl_vertex_iasm m_asm{};
        uint m_vao{};

        uint m_ibo{};
        


        
    }; 
} // namespace emt


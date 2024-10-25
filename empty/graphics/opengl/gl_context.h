#pragma once

#include "graphics/context.h"

namespace emt
{
    #define  max_vertex_buffer_binding  32
    class gl_context : public context
    {
        public:
        gl_context(uint cx, uint cy, HWND hwnd, bool vsync);
        ~gl_context();
        
    private:
        void clear_t(float r, float g, float b, float a) override;

        void set_viewports_t(uint count, const viewport* vps) override;
        void set_scissor_t(const rect& rc) override;
        void set_input_layout_t(input_layout* layout) override;

        void set_vertex_buffer_t(
            uint slot,
            uint count,
            vertex_buffer* const* buffers,
            const uint* offset,
            const uint* strides) override;

        void set_index_buffer_t(ibuffer* buffer, format format) override;
        void set_vertex_shader_t(const vertex_shader* shader) override;
        void set_pixel_shader_t(const pixel_shader* shader) override;
        void set_geometry_shader_t(const geometry_shader* shader) override;
        void draw_indexed_t(uint count, uint offset) override;

        void set_uniform_buffer_t(uint index, uniform_buffer* buffer) override;
        void swap_buffers_t() override;

        HGLRC m_glrc{};
        HDC m_dc{};


        struct vertex_memory_layout
        {
            uint slot;
            uint count;
            uint buffers[max_vertex_buffer_binding];
            int offsets[max_vertex_buffer_binding];
            int strides[max_vertex_buffer_binding];
        };

        vertex_memory_layout m_asm{};
        GLfloat m_viewports[max_viewports * 4]{};
        double m_depths[max_viewports * 2];
        uint m_vao{};
        uint m_ibo{};

        uint m_shader_pipeline{};
        
        topology current_topology;

        


        
    }; 

    struct gl_command_list
    {
        /* data */
    };
    
} // namespace emt


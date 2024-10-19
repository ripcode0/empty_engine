#pragma once

#include "core/typedef.h"

namespace emt{
    class context
    {
    public:
        context(uint cx, uint cy, HWND hwnd, graphics_api api, bool vsync);
        virtual ~context();

        //interface api functions
        static void clear(float r, float g, float b, float a);
        static void clear_depth(float value);

        static void set_viewports(uint count, const viewport* vps);
        static void set_scissor(const rect& rc);
        static void set_input_layout(input_layout* layout);
        static void set_vertex_buffer(
            uint slot,
            uint count,
            vertex_buffer* const* buffers,
            const uint* offset,
            const uint* strides);
        static void set_vertex_shader(const vertex_shader* shader);
        static void set_pixel_shader(const pixel_shader* shader);
        static void set_geometry_shader(const geometry_shader* shader);
        static void set_index_buffer(ibuffer* buffer, vertex_format format);
        
        static void draw_indexed(uint count, uint offset);
        
        static void swap_buffers();

        //context abstrct function
        virtual void on_create(uint cx, uint cy, bool vsync){};
        virtual void on_resize(uint cx, uint cy){};
        HWND m_hwnd;
        uint client_width;
        uint client_height;
        inline static graphics_api api = graphics_api::opengl;  
    private:
        virtual void clear_t(float r, float g, float b, float a) = 0;
        virtual void set_viewports_t(uint count, const viewport* vps) = 0;
        virtual void set_scissor_t(const rect& rc) = 0;
        virtual void set_input_layout_t(input_layout* layout) = 0;
        virtual void set_vertex_buffer_t(
            uint slot,
            uint count,
            vertex_buffer* const* buffers,
            const uint* offset,
            const uint* strides) = 0;
        virtual void set_index_buffer_t(ibuffer* buffer, vertex_format format) = 0;

        virtual void set_vertex_shader_t(const vertex_shader* shader) = 0;
        virtual void set_pixel_shader_t(const pixel_shader* shader) = 0;
        virtual void set_geometry_shader_t(const geometry_shader* shader) = 0;
        virtual void draw_indexed_t(uint count, uint offset) = 0;
        virtual void swap_buffers_t() = 0;

        inline static context* shared_context{};
        // inline static graphics_api api = graphics_api::opengl;  
        
    };
    
}
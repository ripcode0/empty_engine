#pragma once

#include "core/typedef.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#define max_buffer_count 4068

namespace emt
{
    //typedef std::unordered_map<uint, std::shared_ptr<shader>> shader_cache;
    typedef std::unordered_map<uint, std::shared_ptr<shader>> shader_cache;
    struct graphics
    {
        
        static void reserve_graphics_memories();
        static void release_graphics_memories();

        static void create_buffer(
            const buffer_create_info& info, ibuffer** pp_buffer);

        static void create_vertex_buffer(
            const buffer_create_info& info, vertex_buffer** pp_buffer);

        static void create_index_buffer(
            const buffer_create_info& info, index_buffer** pp_buffer);

        static void release_buffer(ibuffer* buffer);

        static void create_input_layout(
            const input_layout_create_info& info, input_layout** pp_input_layout
        );

        
        static void create_vertex_shader(const char* file, vertex_shader** pp_shader);
        static void create_pixel_shader(const char* file, pixel_shader** pp_shader);
        static void create_geometry_shader(const char* file, geometry_shader** pp_shader);

    private:
        inline static std::vector<std::shared_ptr<ibuffer>> m_buffers;        
        inline static std::unordered_map<std::size_t, std::shared_ptr<input_layout>> m_input_layouts;
        //inline static std::unordered_map<uint, std::shared_ptr<shader>> m_shaders;
        inline static shader_cache m_shaders;
        inline static buffer_pool<ibuffer>* m_buffer_cache;

    };
    
    
} // namespace emt

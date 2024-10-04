#pragma once

#include "core/typedef.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

namespace emt
{
    
    
    struct graphics
    {
        static void init();
        static void release();

        static void create_buffer(
            const buffer_create_info& info, ibuffer** pp_buffer);

        static void create_input_layout(
            const input_layout_create_info& info, input_layout** pp_input_layout
        );

        static void create_shader(const char* file, shader_type type, shader** pp_shader);

    private:
        static std::vector<std::shared_ptr<ibuffer>> m_buffers;        
        inline static std::unordered_map<std::size_t, std::shared_ptr<input_layout>> m_input_layouts;
        inline static std::unordered_map<std::string, std::shared_ptr<shader>> m_shaders;

    };
    
    
} // namespace emt

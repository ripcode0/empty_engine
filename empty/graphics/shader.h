#pragma once

#include "core/typedef.h"

namespace emt
{
    struct shader
    {
        shader(shader_type type) : type(type) {}
        shader_type type;
        uint hash_id;
    };

    struct vertex_shader : shader { 
        vertex_shader() : shader(shader_type::vertex) {}        
    };

    struct pixel_shader : shader { 
        pixel_shader() : shader(shader_type::pixel) {}        
    };

    
    struct geometry_shader : shader { 
        geometry_shader() : shader(shader_type::geometry) {}        
    };
    
    
    
    
    
    
} // namespace emt

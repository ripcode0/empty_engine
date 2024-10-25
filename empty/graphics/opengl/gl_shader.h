#pragma once

#include "graphics/shader.h"

namespace emt
{
    struct gl_vertex_shader : vertex_shader
    {
        gl_vertex_shader(const char* filename);
        virtual~gl_vertex_shader();
        uint gpu_shader_id;
    };
    
    struct gl_pixel_shader : pixel_shader
    {
        gl_pixel_shader(const char* filename);
        virtual~gl_pixel_shader();
        uint gpu_shader_id;
    };

    struct gl_geometry_shader : geometry_shader
    {
        gl_geometry_shader(const char* filename);
        virtual~gl_geometry_shader();
        uint gpu_shader_id;
    };

    struct gl_compute_shader : compute_shader
    {
        gl_compute_shader(const char* filename);
        virtual~gl_compute_shader();
        uint gpu_shader_id;
    };
    
} // namespace emt

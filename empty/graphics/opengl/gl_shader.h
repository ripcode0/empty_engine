#pragma once

#include "graphics/shader.h"

namespace emt
{
    struct gl_shader : shader
    {
        gl_shader(const char* filename, shader_type type);
        
        operator GLuint(){
            return program;
        }
        GLuint program;
    };
    
} // namespace emt

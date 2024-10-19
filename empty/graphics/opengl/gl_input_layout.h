#pragma once

#include "graphics/input_layout.h"

namespace emt
{
    struct gl_input_layout : input_layout
    {
        gl_input_layout(const input_layout_create_info& info);
        virtual~gl_input_layout();
        
        uint vao;
    };
    
} // namespace emt

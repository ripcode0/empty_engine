#pragma once

#include "core/typedef.h"

namespace emt
{
    struct graphics_pipeline
    {
        topology topology;
        vertex_shader* vs;
        pixel_shader* ps;
    };
    
} // namespace emt

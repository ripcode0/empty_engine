#pragma once

#include "core/typedef.h"

namespace emt
{
    struct ibuffer //interface of buffer
    {
        bufffer_type type = bufffer_type::unkown;
    };
    
    struct vertex_buffer : ibuffer
    {
        uint id;
    };
    
} // namespace emt

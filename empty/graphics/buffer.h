#pragma once

#include "core/typedef.h"
#include <string>

namespace emt
{
    struct ibuffer //interface of buffer
    {
        virtual~ibuffer() = default;
        ibuffer(buffer_type type = buffer_type::unkown) : id(0), type(type) {}
        uint id;
        buffer_type type;
    };

    struct vertex_buffer : ibuffer{
        virtual~vertex_buffer() = default;
        vertex_buffer() : ibuffer(buffer_type::vertex){}
    };
    
    struct index_buffer : ibuffer{
        index_buffer() : ibuffer(buffer_type::index){}
    };

    struct uniform_buffer : ibuffer{
        uniform_buffer() : ibuffer(buffer_type::uniform){}
    };
} // namespace emt

#pragma once

#include "graphics/buffer.h"

namespace emt
{
    struct gl_vertex_buffer : vertex_buffer
    {
        explicit gl_vertex_buffer(const buffer_create_info& info);
        virtual~gl_vertex_buffer();
        uint handle;
    };

    struct gl_index_buffer : index_buffer
    {
        explicit gl_index_buffer(const buffer_create_info& info);
        virtual~gl_index_buffer();

        uint handle;
    };
    
    struct gl_uniform_buffer : uniform_buffer
    {
        explicit gl_uniform_buffer(const buffer_create_info& info);
        virtual~gl_uniform_buffer();

        uint handle;
    };
} // namespace emt

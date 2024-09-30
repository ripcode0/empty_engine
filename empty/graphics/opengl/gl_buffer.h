#pragma once

#include "graphics/buffer.h"

namespace emt
{
    struct gl_vertex_buffer : vertex_buffer
    {
        explicit gl_vertex_buffer(const buffer_create_info& info);
        ~gl_vertex_buffer();
        uint m_buffer;
    };

    struct gl_index_buffer : ibuffer
    {
        explicit gl_index_buffer(const buffer_create_info& info);
        ~gl_index_buffer();

        uint m_buffer;
    };
    
    
} // namespace emt

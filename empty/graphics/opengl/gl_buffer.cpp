#include "gl_buffer.h"
#include <assert.h>
#include "graphics/opengl/gl_config.h"

namespace emt
{
    gl_vertex_buffer::gl_vertex_buffer(const buffer_create_info &info)
    {
        assert(info.type == buffer_type::vertex);        
        type = info.type;
        glCreateBuffers(1, &handle);

        //glNamedBufferData(m_buffer, info.size, info.p_data, GL_STATIC_DRAW);   
        glNamedBufferStorage(handle, info.size, info.p_data, 0);

    }

    gl_vertex_buffer::~gl_vertex_buffer()
    {
        glDeleteBuffers(1, &handle);
    }

    gl_index_buffer::gl_index_buffer(const buffer_create_info &info)
    {
        assert(info.type == buffer_type::index);        
        type = info.type;
        glCreateBuffers(1, &handle);
        glNamedBufferStorage(handle, info.size, info.p_data, 0);
    }

    gl_index_buffer::~gl_index_buffer()
    {
        glDeleteBuffers(1, &handle);
    }

    gl_uniform_buffer::~gl_uniform_buffer()
    {
        glDeleteBuffers(1, &handle);
    }

} // namespace emt

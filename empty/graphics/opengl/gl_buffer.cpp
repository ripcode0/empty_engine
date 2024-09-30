#include "gl_buffer.h"
#include <assert.h>
#include "graphics/opengl/gl_config.h"

namespace emt
{
    gl_vertex_buffer::gl_vertex_buffer(const buffer_create_info &info)
    {
        assert(info.type == bufffer_type::vertex);        
        type = info.type;
        glCreateBuffers(1, &m_buffer);

        //glNamedBufferData(m_buffer, info.size, info.p_data, GL_STATIC_DRAW);   
        glNamedBufferStorage(m_buffer, info.size, info.p_data, 0);

    }

    gl_vertex_buffer::~gl_vertex_buffer()
    {
        glDeleteBuffers(1, &m_buffer);
    }

    gl_index_buffer::gl_index_buffer(const buffer_create_info &info)
    {
        assert(info.type == bufffer_type::index);        
        type = info.type;
        glCreateBuffers(1, &m_buffer);
        glNamedBufferStorage(m_buffer, info.size, info.p_data, 0);
    }

    gl_index_buffer::~gl_index_buffer()
    {
        glDeleteBuffers(1, &m_buffer);
    }

} // namespace emt

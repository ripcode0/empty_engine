#include "gl_input_layout.h"
#include "graphics/opengl/gl_config.h"

namespace emt
{
    GLenum get_gl_format(const vertex_format& format){
        switch (format)
        {
        case vertex_format_byte: return GL_BYTE;
        case vertex_format_int: return GL_INT;
        case vertex_format_uint: return GL_UNSIGNED_INT;
        case vertex_format_short: return GL_SHORT;
        case vertex_format_float: return GL_FLOAT;
        case vertex_format_double: return GL_DOUBLE;
        default:
            return 0;
        }
    };
    gl_input_layout::gl_input_layout(const input_layout_create_info &info)
    {
        static uint next_id = 0;
        id = next_id++;

        glCreateVertexArrays(1, &m_vao);
        for(uint i =0; i < info.attr_size; ++i){
            vertex_attrib& attr = info.p_attrib[i];
            glEnableVertexArrayAttrib(m_vao, i);
            glVertexArrayAttribFormat(m_vao, attr.location, attr.format_size, get_gl_format(attr.format),
             GL_FALSE, attr.offset);
            glVertexArrayAttribBinding(m_vao, i, 0);
        }
    }    
} // namespace emt


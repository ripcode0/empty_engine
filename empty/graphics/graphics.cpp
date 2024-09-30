#include "graphics.h"
#include "graphics/buffer.h"
#include "graphics/context.h"
#include "graphics/opengl/gl_buffer.h"
#include "graphics/opengl/gl_input_layout.h"
#include "graphics/hash_table.h"

namespace emt
{
    std::vector<std::shared_ptr<ibuffer>> graphics::m_buffers;

    void graphics::init()
    {

    }

    void graphics::release()
    {
        m_buffers.clear();
    }

    void graphics::create_vertex_buffer(
        const buffer_create_info &info, ibuffer** pp_buffer
    )
    {
        std::shared_ptr<ibuffer> buffer = nullptr;
    
        switch (graphics_context::api)
        {
        case graphics_api::opengl:
            {
                switch (info.type)
                {
                case bufffer_type::vertex:
                    {
                        buffer = std::make_shared<gl_vertex_buffer>(info);
                        gl_vertex_buffer* vertex_buffer = static_cast<emt::gl_vertex_buffer*>(buffer.get());
                        vertex_buffer->id = 10;
                        
                    }break;
                case bufffer_type::index:
                    {
                        buffer = std::make_shared<gl_index_buffer>(info);
                    }break;
                default:
                    break;
                }
            }
            break;
        
        default:
            break;
        }

        *pp_buffer = buffer.get();

        m_buffers.emplace_back(buffer);
    }

    void graphics::create_input_layout(const input_layout_create_info &info, input_layout **pp_input_layout)
    {   
        std::shared_ptr<input_layout> input_layout_ptr{};

        std::size_t hash_id = create_input_layout_hash(info);

        printf("hash id %zu\n", hash_id);

        if(m_input_layouts.find(hash_id) != m_input_layouts.end()){
            printf("founded\n");
            *pp_input_layout =  m_input_layouts[hash_id].get();
            return;
        }

        switch (graphics_context::api)
        {
        case graphics_api::opengl:
            input_layout_ptr = std::make_shared<gl_input_layout>(info);
            break;
        default:
            break;
        }

        *pp_input_layout = input_layout_ptr.get();
        std::pair<std::size_t, std::shared_ptr<input_layout>> sets(hash_id, input_layout_ptr);
        m_input_layouts.insert(sets);
    }

    

} // namespace emt


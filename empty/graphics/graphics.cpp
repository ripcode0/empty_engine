#include "graphics.h"
#include "graphics/buffer.h"
#include "graphics/context.h"
#include "graphics/opengl/gl_buffer.h"
#include "graphics/opengl/gl_input_layout.h"
#include "graphics/hash_table.h"
#include "graphics/opengl/gl_shader.h"
#include "graphics/buffer_pool.h"
#include "core/config.h"
namespace emt
{
    //buffer_pool<ibuffer>* graphics::m_buffer_cache{};
    
    void graphics::reserve_graphics_memories()
    {
        if(!m_buffer_cache){
            m_buffer_cache = emt_new buffer_pool<ibuffer>(max_buffer_count);
            printf("[emt] create the buffer pool %zu size\n", sizeof(ibuffer*) * max_buffer_count);
        }
        
    }

    void graphics::release_graphics_memories()
    {
        safe_delete(m_buffer_cache);
        m_buffers.clear();
    }

    void graphics::create_buffer(
        const buffer_create_info &info, ibuffer** pp_buffer
    )
    {
        ibuffer* buffer = nullptr;

        switch (context::api)
        {
        case graphics_api::opengl:
            {
                switch (info.type)
                {
                case buffer_type::vertex: 
                    buffer = m_buffer_cache->alloc<gl_vertex_buffer>(info);
                    break;
                case buffer_type::index:
                    buffer = m_buffer_cache->alloc<gl_index_buffer>(info);
                    break;
                default:
                    break;
                }
            }
            break;
        
        default:
            break;
        }

        *pp_buffer = buffer;
    }

    void graphics::create_vertex_buffer(const buffer_create_info &info, vertex_buffer **pp_buffer)
    {
        assert_msg(info.type == buffer_type::vertex, "the type dose not match, please check buffer_create_info");

        vertex_buffer* p_buffer{};

        switch (context::api)
        {
        case graphics_api::opengl:
            p_buffer = (vertex_buffer*)m_buffer_cache->alloc<gl_vertex_buffer>(info);
            break;
        
        default:
            break;
        }
        *pp_buffer = p_buffer;
    }

    void graphics::create_index_buffer(const buffer_create_info &info, index_buffer **pp_buffer)
    {
        assert_msg(info.type == buffer_type::index, "the type dose not match, please check buffer_create_info");

        index_buffer* p_buffer{};

        switch (context::api)
        {
        case graphics_api::opengl:
            p_buffer = (index_buffer*)m_buffer_cache->alloc<gl_index_buffer>(info);
            break;
        
        default:
            break;
        }
        *pp_buffer = p_buffer;
    }

    void graphics::release_buffer(ibuffer* buffer)
    {
        m_buffer_cache->release(buffer);
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

        switch (context::api)
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

    std::string get_extension(){
        switch (context::api)
        {
        case graphics_api::opengl: return GLSL_EXTENTION;
        case graphics_api::dx11: return HLSL_EXTENSION;
        default: return ".none";
        }
    }

    std::string get_shader_path(){
        switch (context::api)
        {
        case graphics_api::opengl: return GLSL_PATH;
        case graphics_api::dx11: return HLSL_PATH;
        default: return ".none";
        }
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<shader, T>::value, T*>::type
    create_shader_from_cache(const char* filename, shader_type type, shader_cache& cache)
    {
        std::string shader_str(get_shader_path() + filename);
        
        shader_str += get_extension();

        std::hash<std::string> hasher;
        uint id = (uint)hasher(shader_str);
        std::size_t id_t = hasher(shader_str);


        auto found = cache.find(id);

        if(found != cache.end()){
            T* shader = (T*)found->second.get();
            if(shader->type != type){
                return nullptr;
                
            }
            return shader;
        }
        auto shader_ptr = std::make_shared<T>(shader_str.c_str());
        shader_ptr->hash_id = id;

        cache.insert(std::pair<uint, std::shared_ptr<shader>>(id, shader_ptr));
        return shader_ptr.get();
    }

    void graphics::create_vertex_shader(const char* file, vertex_shader **pp_shader)
    {
        vertex_shader* p_shader = nullptr;
        switch (context::api)
        {
        case graphics_api::opengl:
            p_shader = create_shader_from_cache<gl_vertex_shader>(file, shader_type::vertex, m_shaders);    
            break;
        case graphics_api::dx11:
            break;
        default:
            break;
        }
        
        *pp_shader = p_shader;
    }

    void graphics::create_pixel_shader(const char *file, pixel_shader **pp_shader)
    {
        pixel_shader* p_shader = nullptr;
        switch (context::api)
        {
        case graphics_api::opengl:
            p_shader = create_shader_from_cache<gl_pixel_shader>(file, shader_type::pixel, m_shaders);    
            break;
        case graphics_api::dx11:
            break;
        default:
            break;
        }
        
        *pp_shader = p_shader;
    }

    void graphics::create_geometry_shader(const char *file, geometry_shader **pp_shader)
    {
        geometry_shader* p_shader = nullptr;
        switch (context::api)
        {
        case graphics_api::opengl:
            p_shader = create_shader_from_cache<gl_geometry_shader>(file, shader_type::geometry, m_shaders);    
            break;
        case graphics_api::dx11:
            break;
        default:
            break;
        }
        
        *pp_shader = p_shader;
    }

} // namespace emt


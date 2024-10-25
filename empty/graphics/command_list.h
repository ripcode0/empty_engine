#pragma once

#include "core/typedef.h"
#include <vector>

typedef union { void* ptr; int id; } emt_handle;
struct emt_vec2 { float x, y;};
struct emt_rect { float x, y, w, h;};
struct emt_image { emt_handle handle; uint w,h; emt_rect rc;};


namespace emt
{
    
    
    struct draw_command
    {
        rect clip;
        uint texture_id;
        uint vtx_offset;
        uint idx_offset;
        uint count;
    };

    struct draw_command_list
    {
        std::vector<draw_command>   cmd_buffers;
        std::vector<uint32>         index_buffers;
        std::vector<vertex_pc>      vertex_buffers;

        vertex_pc*  write_vertex_buffer;
        uint*       write_index_buffer;

    };
    
    



    
    
} // namespace emt

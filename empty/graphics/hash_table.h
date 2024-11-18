#pragma once

#include <unordered_map>

#include "core/typedef.h"

namespace emt
{
    bool operator==(const vertex_attrib& lhs, const vertex_attrib& rhs)
    {
        return lhs.location == rhs.location &&
           lhs.format == rhs.format &&
           //lhs.format_size == rhs.format_size &&
           lhs.stride == rhs.stride &&
           lhs.offset == rhs.offset;
    }
    struct vertex_attrib_hash
    {
        std::size_t operator()(const vertex_attrib& attr){
            std::size_t hash0 = std::hash<uint>()(attr.location);
            std::size_t hash1 = std::hash<uint>()(attr.format);
            //std::size_t hash2 = std::hash<uint>()(attr.format_size);
            std::size_t hash2 = std::hash<uint>()(attr.stride);
            std::size_t hash3 = std::hash<uint>()(attr.offset);
            return hash0 ^ (hash1 << 1) ^ (hash2 << 2) ^ (hash3 << 3);
        }
    };

    inline std::size_t create_input_layout_hash(const input_layout_create_info& info){
        std::size_t hash = 0;
        vertex_attrib_hash hasher;
        for(uint i = 0; i < info.attr_size; ++i){
            hash ^= (hasher(info.p_attrib[i]) << i);
        }

        return hash;
    }

    
} // namespace emt



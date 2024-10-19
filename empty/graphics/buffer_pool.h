#pragma once

#include "core/typedef.h"
#include <queue>

namespace emt
{
    template<typename, typename = std::void_t<>>
    struct has_member_id : std::false_type {};

    template<typename T>
    struct has_member_id<T, std::void_t<decltype(std::declval<T>().id)>> : std::true_type {};

    template<typename T>
    struct buffer_pool
    {
        buffer_pool(uint capacity) : capacity(capacity), used_count(0)
        {
            buffer_list = new T*[capacity];
            memset(buffer_list, 0, sizeof(T*) * capacity);
            for(uint i = 0; i < capacity; ++i){
                unused_indices.push_back(i);
            }
        }
        ~buffer_pool(){
            for(uint i = 0; i < capacity; ++i){
                delete buffer_list[i];
            }

            delete[] buffer_list;
        }

        template<typename Type, typename... Args>
        T* alloc(Args&&... args){
            static_assert(std::is_base_of<T, Type>::value, "derived class must be from buffer");
            static_assert(has_member_id<T>::value, "base class must be has id member variables");
            if(unused_indices.empty()){
                printf("[warninig] buffer overflow...\n");
                return nullptr;
            }

            uint index = unused_indices.front();

            unused_indices.pop_front();

            buffer_list[index] = new Type(std::forward<Args>(args)...);
            buffer_list[index]->id = index;
            switch (buffer_list[index]->type)
            {
            case buffer_type::vertex:   type_count[0]++; break;
            case buffer_type::index:    type_count[1]++; break;
            case buffer_type::uniform:  type_count[2]++; break;
            default:
                break;
            }
            used_count++;
            return static_cast<T*>(buffer_list[index]);
        }

        void release(T* buffer){
            if(!buffer) return;
            uint index = buffer->id;

            if(index < capacity && buffer_list[index] != nullptr){
                delete buffer_list[index];
                buffer_list[index] = nullptr;
                unused_indices.push_front(index);
                used_count--;
            }
        }

        uint capacity;
        uint used_count;
        uint type_count[3]{};
        T** buffer_list;
        std::deque<uint> unused_indices;
    };
    
} // namespace emt

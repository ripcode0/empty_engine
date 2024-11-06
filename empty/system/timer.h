#pragma once

#include <chrono>

namespace emt
{
    struct fps_timer
    {
        fps_timer();

        void begin_frame();
        void end_frame();

        int frame_count{};
        float fps{};
        float delta{};
        
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point last_time;
    };
    
    
} // namespace emt

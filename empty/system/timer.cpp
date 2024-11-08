#include "timer.h"

namespace emt
{
    fps_timer::fps_timer()
    {
    }

    void fps_timer::begin_frame()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void fps_timer::end_frame()
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration<float>(current_time - start_time).count();

        frame_count++;

        if(std::chrono::duration<float>(current_time - last_time).count() >= 1.0f)
        {
            fps = frame_count / std::chrono::duration<float>(current_time - last_time).count();
            frame_count = 0;
            last_time = current_time;

            printf("%f\n", fps);
        }
    }

} // namespace emt

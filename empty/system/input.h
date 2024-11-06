#pragma once

#include "core/typedef.h"

namespace emt
{
    struct input
    {
        input() = default;
        input(const input& rhs) = delete;
        input& operator=(const input& rhs) = delete;

        static void init_frame(HWND hwnd);
        static void update_frame();

    //private:
        inline static float current_pos[2]{};
        inline static float last_pos[2]{};
        inline static float delta[2]{};

        inline static HWND current_hwnd{};

        static bool is_key_pressed(int key);
    };
    
    
} // namespace emt

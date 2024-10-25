#include "input.h"
#include "core/config.h"

namespace emt
{
    void input::init_frame(HWND hwnd)
    {
        current_hwnd = hwnd;
    }

    void input::update_frame()
    {
        static bool first_updated = false;
        POINT pt{};

        GetCursorPos(&pt);

        if(current_hwnd){
            ::ScreenToClient(current_hwnd, &pt);
        }

        current_pos[0] = (float)pt.x;
        current_pos[1] = (float)pt.y;

        if(!first_updated){
            memcpy(&last_pos, current_pos, sizeof(float) * 2);
            first_updated;
        }

        if(last_pos[0] != current_pos[0] || last_pos[1] != current_pos[1]){
            delta[0] = current_pos[0] - last_pos[0];
            delta[1] = current_pos[1] - last_pos[1];
        }
        else {
            delta[0] = 0.f;
            delta[1] = 0.f;
        }

    memcpy(&last_pos, &current_pos, sizeof(float) * 2);

    }

} // namespace emt


#pragma once

#include "core/typedef.h"

namespace emt
{
    struct window_create_info
    {
        uint cx;
        uint cy;
        const char* title;
        graphics_api api_type;
    };
    
    struct window
    {
        explicit window(const window_create_info& info);
        ~window();
        uint m_cx;
        uint m_cy;
        
        char m_title[128]{};

        HWND m_hwnd;
        context* m_context;

        int exec(scene* scene);
    };
}



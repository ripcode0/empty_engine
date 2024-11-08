#pragma once

#include "core/typedef.h"

namespace emt
{
    struct graphics_context
    {
        graphics_context(uint cx, uint cy, HWND hwnd, bool vsync = false);
        graphics_context(const graphics_context& rhs) = delete;
        graphics_context& operator=(const graphics_context& rhs) = delete;

        virtual void set_viewport(const viewport& viewport) = 0;

        inline static graphics_context* get_shared_context(){
            return shared_context;
        }
    private:
        uint cx;
        uint cy;
        HWND hwnd;
        bool vsync;

        inline static graphics_context* shared_context{};
    };
    

    struct gl_graphics_context : graphics_context
    {
        gl_graphics_context(uint cx, uint cy, HWND hwnd, bool vsync);

        virtual void set_viewport(const viewport& vp) override;
    };
    

} // namespace emt

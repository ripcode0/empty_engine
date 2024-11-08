#include "graphics_context.h"
#include "graphics/opengl/gl_config.h"

namespace emt
{
    graphics_context::graphics_context(uint cx, uint cy, HWND hwnd, bool vsync)
        : cx(cx), cy(cy), hwnd(hwnd), vsync(vsync)
    {
        if(!shared_context){
            shared_context = this;
        }
    }

    gl_graphics_context::gl_graphics_context(uint cx, uint cy, HWND hwnd, bool vsync)
        : graphics_context(cx, cy, hwnd, vsync)
    {

    }

    void gl_graphics_context::set_viewport(const viewport &vp)
    {
        glViewport(vp.x, vp.y, vp.width, vp.height);
        
    }

} // namespace emt

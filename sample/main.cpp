
#include "window/window.h"
#include "graphics/dx12/dx12_buffer.h"

using namespace emt;

#include "graphics/graphics.h"
#include "graphics/context.h"
#include "scenes/triangle_scene.h"
#include "core/config.h"
#include "scenes/opengl/dsa_scene.h"



int main(int args, char* argv[])
{
    window_create_info info{};
    info.cx = 1280;
    info.cy = 720;
    info.api_type = graphics_api::opengl;
    
    emt::window window(info);
    
    basic_scene scene_00;
    dsa_scene scene_01;
    



    int res = window.exec(&scene_00);

    return res;
}

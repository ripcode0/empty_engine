#pragma once

#include "core/typedef.h"

namespace emt
{
    struct camera
    {
        camera(float fov, float aspect, float znear, float zfar);
        

        void internal_update();

        mat4x4 projection;
        mat4x4 view;
        mat4x4 local;

        float fovy;
        float znear;
        float zfar;
        float aspect_ratio;

        vec3f pos;
        vec3f rot;

        
        vec3f forward;
        vec3f up;
        vec3f right;
    };
    
} // namespace emt

#pragma once

#include "core/typedef.h"

namespace emt
{
    typedef void (*pfn_camera_controller)(camera*, float);
    struct camera
    {
        camera(float fov, float aspect, float znear, float zfar);

        void look_at(const vec3f& eye, const vec3f& at);
        
        void update_frame(float dt);

        void internal_update();

        mat4x4 proj;
        mat4x4 view;
        mat4x4 local;

        float fovy;
        float znear;
        float zfar;
        float aspect_ratio;

        vec3f pos;
        vec3f rot;
        float yaw {};
        float pitch{};
        
        vec3f forward;
        vec3f up;
        vec3f right;

        pfn_camera_controller m_ctrl{};

        inline static void fps_movement(camera* camera, float dt);
    };
    
} // namespace emt

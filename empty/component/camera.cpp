#include "camera.h"
#include "system/input.h"

namespace emt
{
    camera::camera(float fov, float aspect, float znear, float zfar)
        : fovy(fov), aspect_ratio(aspect), znear(znear), zfar(zfar)
    {
        proj = mat4x4::perspective_lh(fovy, aspect_ratio, znear, zfar);

        forward = {0.0f, 0.0f, 1.0f};    
        up      = {0.0f, 1.0f, 0.0f};
        right   = {1.0f, 0.0f, 0.0f};

        internal_update();

        m_ctrl = &camera::fps_movement;
    }
    void camera::look_at(const vec3f &eye, const vec3f &at)
    {
        pos = eye;
        forward = (at - pos).normalized();
        right = vec3f::cross(vec3f(0.f, 1.f, 0.f), forward).normalized();
        up = vec3f::cross(forward, right).normalized();


        pitch = -std::asinf(forward.y) * DEGREES;
        yaw = std::atan2f(forward.x, forward.z) * DEGREES;

        internal_update();
    }
    void camera::update_frame(float dt)
    {
        //TODO :: controller of input function
        if(m_ctrl){
            m_ctrl(this, dt);
        }

        internal_update();
    }

    void camera::internal_update()
    {
        local = {
             right.x,    up.x, forward.x, pos.x,
             right.y,    up.y, forward.y, pos.y,
             right.z,    up.z, forward.z, pos.z,
                0.0f,    0.0f,      0.0f,  1.0f
        };

        float x = -vec3f::dot(right, pos);
        float y = -vec3f::dot(up, pos);
        float z = -vec3f::dot(forward, pos);

        view = {
            right.x   ,right.y,     right.z,    x,
            up.x      ,up.y,        up.z,       y,
            forward.x ,forward.y,   forward.z,  z,
            0.f, 0.f, 0.f, 1.f
        };
    }

    void camera::fps_movement(camera *camera, float dt)
    {
        float speed = 3.33f;
        const float sensor = 0.05f;

        if(input::is_key_pressed(key::lmb)){
            camera->yaw     += input::delta[0] * sensor;
            camera->pitch   -= input::delta[1] * sensor;
        }
        

        //forward axis
        float pitch = camera->pitch;
        float yaw =  camera->yaw;

        // camera->forward.x = cos(pitch) * cos(yaw);
        // camera->forward.y = sin(pitch);
        // camera->forward.z = -cos(pitch) * sin(yaw);

        mat4x4 r = mat4x4::yaw_pitch_roll(yaw, pitch, 0.f);

        camera->right   = vec3f(r[0][0], r[1][0], r[2][0]).normalized();
        camera->up      = vec3f(r[0][1], r[1][1], r[2][1]).normalized();
        camera->forward = vec3f(r[0][2], r[1][2], r[2][2]).normalized();


        if(input::is_key_pressed('W')){
            camera->pos += camera->forward * speed * dt;
        }
        if(input::is_key_pressed('S')){
            camera->pos -= camera->forward * speed * dt;
        }

        camera->internal_update();
        
        
    }
} // namespace emt

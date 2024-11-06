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
        float sensor = 0.1f;
        camera->yaw += input::delta[0] * sensor;
        camera->pitch -= input::delta[1] * sensor;

        camera->forward.x = cos(camera->yaw) * cos(camera->pitch);
        camera->forward.y = sin(camera->pitch);
        camera->forward.z = sin(camera->yaw) * cos(camera->pitch);
        camera->forward = camera->forward.normalized();



        if(input::is_key_pressed('W')){
            camera->pos += camera->forward * speed * dt;
        }
        if(input::is_key_pressed('S')){
            camera->pos -= camera->forward * speed * dt;
        }

        
        
        
    }
} // namespace emt

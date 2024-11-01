#include "camera.h"

namespace emt
{
    camera::camera(float fov, float aspect, float znear, float zfar)
        : fovy(fov), aspect_ratio(aspect), znear(znear), zfar(zfar)
    {
        projection = mat4x4::perspective_lh(fovy, aspect_ratio, znear, zfar);

        forward = {0.0f, 0.0f, 1.0f};    
        up      = {0.0f, 1.0f, 0.0f};
        right   = {1.0f, 0.0f, 0.0f};

        internal_update();
    }
    void camera::look_at(const vec3f &eye, const vec3f &at)
    {
        pos = eye;
        forward = (pos - eye).normalized();
        right = vec3f::cross(vec3f(0.f, 1.f, 0.f), forward).normalized();
        up = vec3f::cross(forward, right).normalized();

        internal_update();
    }
    void camera::update_frame(float dt)
    {
        //TODO :: controller of input function

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
            right.x , right.y, right.z, x,
            right.x , right.y, right.z, y,
            right.x , right.y, right.z, z,
            0.f, 0.f, 0.f, 1.f
        };
    }
} // namespace emt

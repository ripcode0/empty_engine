#pragma once

struct vec3
{
    vec3() : x(0.f), y(0.f), z(0.f) {}
    vec3(float x) : x(x), y(x), z(x) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    float x,y,z;
};

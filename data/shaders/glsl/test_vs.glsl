#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;


out gl_PerVertex { vec4 gl_Position; };



void main()
{
    gl_Position = vec4(pos, 1);
}


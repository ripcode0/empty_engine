#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in mat4 instanced_mat;

out gl_PerVertex { vec4 gl_Position; };

void main()
{
    gl_Position = vec4(pos, 1);
}
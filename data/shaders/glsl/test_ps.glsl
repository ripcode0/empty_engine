#version 450 core

out vec4 pixel_color;

in struct {
    vec3 color;
}ps_in;

void main()
{
    pixel_color = vec4(ps_in.color,1);
}

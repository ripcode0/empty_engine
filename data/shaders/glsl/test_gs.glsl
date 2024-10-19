#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 32) out;

void main()
{
    for(int i =0; i < 3; i++){
        gl_Position = gl_in[i].gl_Position + vec4(-0.1, -0.1, 0,0);
        EmitVertex();
        gl_Position = gl_in[i].gl_Position + vec4(0.1, -0.1, 0,0);
        EmitVertex();
        gl_Position = gl_in[i].gl_Position + vec4(0.0, 0.1, 0,0);
        EmitVertex();
        EndPrimitive();
    }
};
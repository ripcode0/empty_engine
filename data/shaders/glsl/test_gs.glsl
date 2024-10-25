#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 32) out;

out struct
{
    vec3 color;
}ps_in;

void main()
{
    ps_in.color = vec3(0.7,0.7,0.7);

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
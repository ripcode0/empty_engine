#version 450

// #extension GL_NV_shader_buffer_load : require
// #extension GL_NV_gpu_shader5 : enable

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

//layout(buffer_address) readonly uniform uint64_t vbo;
layout (std140, binding = 0) uniform ubo{
    vec3 pitch;
};

out gl_PerVertex { vec4 gl_Position; };

out struct {
    vec3 color;
}ps_in;


void main()
{
    //vec3 pos = fetchFromBuffer(vbo, gl_VertexID);
    gl_Position = vec4(pos * pitch, 1);
    ps_in.color = pitch;
}


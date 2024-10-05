#pragma once

#include "core/defines.h"

typedef unsigned char   uint8, byte; 
typedef unsigned int    uint, uint32;

//============ OpenGL4 Foward Decalre =============
struct	HWND__;
typedef HWND__ *HWND;
struct HDC__;
typedef HDC__ *HDC;
struct HGLRC__;
typedef HGLRC__ *HGLRC;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLenum;

//========== DirectX11 Foward Decalre =============

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11ShaderResourceView;
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D11SamplerState;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct D3D11_VIEWPORT;

//engine
namespace emt
{
    enum class graphics_api : uint
    {
        dx11 = 0x0, dx12, opengl, vulkan
    };

    struct vertex_buffer_create_info
    {
        void* p_data;
        uint  size;
        uint  stride;
    };

    struct index_buffer_create_info
    {
        void* p_data;
        uint size;
    };

    enum class bufffer_type
    {
        vertex, index, uniform, unkown
    };

    enum class buffer_usage
    {
        gpu_read, gpu_read_write
    };
    
    struct buffer_create_info
    {
        bufffer_type type;
        uint size;
        void* p_data;
    };

    enum vertex_format
    {
        vertex_format_byte,
        vertex_format_int,
        vertex_format_uint,
        vertex_format_short,
        vertex_format_float,
        vertex_format_double
    };

    enum class format : uint
    {
        r8_uint,
        rg8_uint,
        rgb8_uint,
        rgba8_uint,
        rgba8,
        r16,
        rgb16,
        rgba16,
        r32,
        rgb32, 
        rgba32
    };

    enum furmat{
        r8_uint,
        r8_unorm,

    };
    

    struct vertex_attrib
    {
        uint location;
        vertex_format format;
        uint format_size;
        uint stride;
        uint offset;
    };
    
    
    struct input_layout_create_info
    {
        vertex_attrib* p_attrib;
        uint attr_size;
    };

    enum class shader_type : uint
    {
        vertex, pixel, geometry, hull, compute
    };
    
    class scene;
    class context;

    struct ibuffer;
    struct vertex_buffer;
    struct index_buffer;
    struct input_layout;

    struct shader;

    //opengl struct
    struct gl_input_layout;
    struct gl_vertex_buffer;
    struct gl_index_buffer;
}

#include "vertex_type.h"




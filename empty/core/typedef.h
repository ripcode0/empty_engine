#pragma once

#include "core/defines.h"
#include <stdint.h>

typedef unsigned char   uint8, byte; 
typedef unsigned int    uint, uint32;
typedef uint64_t uint64;

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

#if defined(_WIN64)
typedef signed long long int GLintptr;
typedef unsigned long long int GLuintptr;
#else
typedef signed long int GLintptr;
typedef unsigned long int GLuintptr;
#endif

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

    struct rect
    {
        uint x, y, width, height;
    };
    

    struct viewport
    {
        float x;
        float y;
        float width;
        float height;
        float min_depth;
        float max_depth;
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

    enum class buffer_type
    {
        vertex, index, uniform, unkown
    };

    enum class buffer_usage
    {
        gpu_read, gpu_read_write
    };
    
    struct buffer_create_info
    {
        buffer_type type;
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

    enum format 
    {
        r8_uint,
        r8_sint,
        r8_unorm,
        r8_snorm,
        r16_float,
        r16_unorm,
        t16_uint,
        r16_sint,
        r16_snorm,
        rg8_uint,
        rb8_sint,
        rb8_unorm,
        rb8_snorm,
        d24_unorm_s8_uint,
        r32_float,
        r32_uint,       //unsigned short
        r32_sint,
        rg16_float,
        rg16_uint,
        rg16_sint,
        rg16_unorm,
        rg16_snorm,
        rgba8_uint,
        rgba8_sint,
        rgba8_unorm,
        rgba8_snorm,
        rgba16_float,
        rgba16_uint,
        rgba16_unorm,
        rgb32_float,
        rgb32_uint,
        rgb32_sint,
        rgba32_float,
        rgba32_uint,
        rgba32_sint
    };

 
   

    struct vertex_attrib
    {
        uint location;
        //vertex_format format;
        format format;
        //uint format_size;
        uint stride;
        uint offset;
        bool instanced;
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

    enum class topology : uint{
        points, lines,line_strip, triangles, triangle_strip
    };
    
    class scene;
    class context;

    struct ibuffer;
    struct vertex_buffer;
    struct index_buffer;
    struct uniform_buffer;
    struct input_layout;

    struct shader;
    struct vertex_shader;
    struct pixel_shader;
    struct geometry_shader;

    //opengl struct
    struct gl_input_layout;
    struct gl_vertex_buffer;
    struct gl_index_buffer;

    //system
    struct camera;
    
    

    //meta
    template<typename T> struct buffer_pool;
}

#include "vertex_type.h"




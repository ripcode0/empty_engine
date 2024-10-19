#pragma once

//macros
#ifdef _MSC_VER
#define stdcall __stdcall
#elif defined(__clang__) || defined(__GNUC__)
#define stdcall __attribute__((stdcall))
#else
#define stdcall
#endif


//graphics

#define max_viewports 12

#ifdef USE_SHADER_EXTENSION 
#define GLSL_EXTENTION ".glsl"
#define HLSL_EXTENSION ".hlsl"
#else
#define GLSL_EXTENTION ""
#define HLSL_EXTENSION ""
#endif

#ifdef USE_SHADER_PATH
#define GLSL_PATH "data/shaders/glsl/"
#define HLSL_PATH "data/shaders/hlsl/"
#else
#define GLSL_PATH ""
#define HLSL_PATH ""
#endif

#define emt_release(x) if(x) { x->release();}
#if defined(_DEBUG) && defined(_MSC_VER) 
#include <crtdbg.h>
#define emt_new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define emt_new new
#endif

#define safe_delete(x) { if((x)) { delete (x); (x) = nullptr; } }
#define safe_release(x) { if((x)) { (x)->Release(); (x) = nullptr; } }

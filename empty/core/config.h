#pragma once

#define safe_release(x) if(x) { x->Release(); x = nullptr;}
#define safe_delete(x) if(x) { delete x; x = nullptr; }
#define safe_reset(x) if(x) { x->Reset(); x = nullptr; }

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// //d3d12
// #include <d3d12.h>
// #include <dxgi1_6.h>

// #include <d3dcompiler.h>
#include <iostream>
#include <stdarg.h>

#define log_error(x, ...) __log_error(x, __FILE__, __LINE__, __VA_ARGS__)

// inline void __log_error(const char* code, const char* filename, int line, ...)
// {
//     va_list args;
//     va_start(args, code);
//     char codeBuffer[256]{};

//     vsnprintf_s(codeBuffer, -1, code, args);

//     filename = (::strchr(filename, '\\') + 1);

//     char buffer[256] {};
//     sprintf_s(buffer, "file : %s\nline : %d\n\n%s\n", filename, line, codeBuffer);

//     MessageBoxA(nullptr, buffer, "fatal error!", MB_OKCANCEL);
// }

inline void __log_error(const char* code, const char* filename, int line, ...)
{
    va_list args;
    va_start(args, line); 

    char codeBuffer[256]{};

    
    vsnprintf_s(codeBuffer, sizeof(codeBuffer), _TRUNCATE, code, args);

    va_end(args);

    filename = (::strrchr(filename, '\\') ? ::strrchr(filename, '\\') + 1 : filename);

    char buffer[256]{};
    sprintf_s(buffer, "file : %s\nline : %d\n\n%s\n", filename, line, codeBuffer);

    MessageBoxA(nullptr, buffer, "fatal error!", MB_OKCANCEL);
}



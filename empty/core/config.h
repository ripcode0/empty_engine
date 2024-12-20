#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// //d3d12
// #include <d3d12.h>
// #include <dxgi1_6.h>

// #include <d3dcompiler.h>
#include <iostream>
#include <stdarg.h>
#include <assert.h>

#define log_error(x, ...) __log_error(x, __FILE__, __LINE__, __VA_ARGS__)

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

    auto res = MessageBoxA(nullptr, buffer, "fatal error!", MB_OKCANCEL);
    if(res == MB_OK) ExitProcess(0);
};

#include <crtdbg.h>

#define assert_msg(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "[assert] : %s\nfile: %s, line: %d\n", msg, __FILE__, __LINE__); \
            abort(); \
        } \
    } while (0)


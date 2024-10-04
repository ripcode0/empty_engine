#pragma once

//macros
#ifdef _MSC_VER
#define stdcall __stdcall
#elif defined(__clang__) || defined(__GNUC__)
#define stdcall __attribute__((stdcall))
#else
#define stdcall
#endif
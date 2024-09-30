#pragma once

#define safe_release(x) if(x) { x->Release(); x = nullptr;}
#define safe_delete(x) if(x) { delete x; x = nullptr; }
#define safe_reset(x) if(x) { x->Reset(); x = nullptr; }

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//d3d12
#include <d3d12.h>
#include <dxgi1_6.h>

#include <d3dcompiler.h>




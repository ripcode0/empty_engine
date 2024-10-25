#include "window.h"
#include <stdlib.h>
#include "window/window_config.h"
#include "graphics/opengl/gl_context.h"
#include "system/scene.h"
#include "system/input.h"

namespace emt
{
    LRESULT wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    window::window(const window_create_info& info)
    {
        WNDCLASSEXA wc{};
        wc.cbSize = sizeof(wc);
        wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = wnd_proc;
        wc.lpszClassName = "empty engine v0.1.0";
        wc.hInstance = GetModuleHandle(nullptr);
        
        RegisterClassExA(&wc);

        int x = (GetSystemMetrics(SM_CXSCREEN) - info.cx) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - info.cy) / 2;

        m_hwnd =  CreateWindowExA(
            NULL, wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW,
            x, y, info.cx, info.cy, nullptr, 0, wc.hInstance, this
        );
        RECT rc{};
        GetClientRect(m_hwnd, &rc);
        uint cx = rc.right - rc.left;
        uint cy = rc.bottom - rc.top;

        m_context = emt_new gl_context(cx, cy, m_hwnd, false);

        ShowWindow(m_hwnd, SW_SHOW);
    }

    window::~window()
    {
    }

    int window::exec(scene* scene)
    {
        if(scene) scene->init_frame();
        input::init_frame(m_hwnd);

        MSG msg{};

        while (msg.message != WM_QUIT)
        {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE){
                    PostQuitMessage(0);
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            if(scene && m_context){
                input::update_frame();
                
                scene->update_frame(0.f);
                scene->render_frame();
            }
            
            
        }

        if(scene) scene->release_frame();
        if(m_context) delete m_context;
        
        return (int)msg.wParam;
    }

    LRESULT wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
        if(msg == WM_CLOSE){
            
            PostQuitMessage(0);
        }
        return DefWindowProc(hwnd, msg, wp, lp);
    }
}
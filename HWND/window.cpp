#include "pch.h"
#include "window.h"
#include <iostream>
LRESULT deletewindow(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    return S_OK;
}
namespace functions {
    void screen_size::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        std::vector<void*> values;
        filldefaultvalues(argumentspointer, values);
        if (values[0]) {
            RECT desktop;
            const HWND hDesktop = GetDesktopWindow();
            GetWindowRect(hDesktop, &desktop);
            *(win::window_xywh*)values[0] = win::window_xywh(
                {
                    (int)desktop.left,
                    (int)desktop.top,
                    (int)(desktop.right - desktop.left),
                    (int)(desktop.bottom - desktop.top)
                }
            );
        }
        else if (errorcodepointer) {
            *errorcodepointer = data::errorvalues::NULLPTR;
        }
    }
    void create_win::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) { 
        std::vector<void*> values;
        filldefaultvalues(argumentspointer, values);
        std::cout << values[0] << std::endl;
        *(win::window**)values[0] = new win::window(
            (HINSTANCE)values[1],
            *(std::wstring*)values[2],
            *(std::wstring*)values[3],
            (HICON)values[4],
            (HCURSOR)values[5],
            *(win::window_xywh*)values[6],
            *(std::vector<basicfunction*>*)values[7]
        );
        (*(win::window**)values[0])->setV((*(win::window**)values[0])->getV());
    }
    void set_win_x::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        (*(win::window**)(*argumentspointer)[0])->setX(*(int*)(*argumentspointer)[1]);
    }
    void set_win_y::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        (*(win::window**)(*argumentspointer)[0])->setY(*(int*)(*argumentspointer)[1]);
    }
    void set_win_w::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        (*(win::window**)(*argumentspointer)[0])->setW(*(int*)(*argumentspointer)[1]);
    }
    void set_win_h::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        (*(win::window**)(*argumentspointer)[0])->setH(*(int*)(*argumentspointer)[1]);
    }
    void set_win_v::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        (*(win::window**)(*argumentspointer)[0])->setV(*(bool*)(*argumentspointer)[1]);
    }
    void set_win_sm::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        (*(win::window**)(*argumentspointer)[0])->setshowmode(*(int*)(*argumentspointer)[1]);
    }
    void get_win_hwnd::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        *(HWND*)(*argumentspointer)[1] = (*(win::window**)(*argumentspointer)[0])->gethwnd();
    }


    void create_msg_loop::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        if (!errorcodepointer) {
            return;		//avoid uncontrollable execution
        }
        std::vector<void*> values;
        filldefaultvalues(argumentspointer, values);
        MSG msg = { 0 };
        while (WM_QUIT != msg.message) {
            if (PeekMessage(&msg, *(HWND*)values[0], 0, 0 /* *(UINT*)values[1], *(UINT*)values[2] */, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else if (values[3]){
                ((basicfunction*)values[3])->execute(argumentspointer, errorcodepointer, forced, stream);
                if (HAS_E) {
                    return;
                }
            }
        }
    }
	namespace win {
        void window_xywh::destruct(void* pointer) {
            deletable_obj::destructor<window_xywh>(pointer);
        }
        window_xywh getscreensize() {
            RECT desktop;
            HWND hDesktop = GetDesktopWindow();
            GetWindowRect(hDesktop, &desktop);
            return window_xywh(
                {
                    (int)desktop.left,
                    (int)desktop.top,
                    (int)(desktop.right - desktop.left),
                    (int)(desktop.bottom - desktop.top)
                }
            );
        }
		window::window(
            HINSTANCE hinstance, 
            std::wstring classname, 
            std::wstring title, 
            HICON hicon, 
            HCURSOR hcursor, 
            window_xywh rect,
            std::vector<function::basicfunction*> winsubproc
        ) : condition(
            initwin(
                hwnd, 
                NULL, 
                classname, 
                title, 
                hicon, 
                hcursor, 
                rect
            )
        ), 
        classname(classname), rect(rect), winsubproc(winsubproc){}
        void window::destruct(void* pointer) {
            deletable_obj::destructor<function::basicfunction>(pointer);
        }
        void window::setX(int xpos) {
            rect.x = xpos;
            MoveWindow(hwnd, rect.x, rect.y, rect.w, rect.h, TRUE);
        }
        void window::setY(int ypos) {
            rect.y = ypos;
            MoveWindow(hwnd, rect.x, rect.y, rect.w, rect.h, TRUE);
        }
        void window::setW(int width) {
            rect.w = width;
            MoveWindow(hwnd, rect.x, rect.y, rect.w, rect.h, TRUE);
        }
        void window::setH(int height) {
            rect.h = height;
            MoveWindow(hwnd, rect.x, rect.y, rect.w, rect.h, TRUE);
        }
        void window::setV(bool visible) {
            this->visible = visible;
            ShowWindow(hwnd, visible & sw_type);
        }
        window_xywh* window::get_xywh() {
            return &rect;
        }
        bool window::getV() {
            return visible;
        }
        void window::setshowmode(int mode) {
            LONG HWNDStyle = GetWindowLong(hwnd, GWL_STYLE);
            LONG HWNDStyleEx = GetWindowLong(hwnd, GWL_EXSTYLE);
            window_xywh screensize = getscreensize();
            switch (mode) {
                case windowshowmode::fullscreen:
                    //полноэкранный режим
                    sw_type = SW_MAXIMIZE;
                    HWNDStyle &= ~WS_BORDER;
                    HWNDStyle &= ~WS_DLGFRAME;
                    HWNDStyle &= ~WS_THICKFRAME;
                    HWNDStyleEx &= ~WS_EX_WINDOWEDGE;
                    SetWindowLong(hwnd, GWL_STYLE, HWNDStyle | WS_POPUP);
                    SetWindowLong(hwnd, GWL_EXSTYLE, HWNDStyleEx | WS_EX_TOPMOST);
                    MoveWindow(hwnd, 0, 0, screensize.w, screensize.h, TRUE);
                    break;
                case windowshowmode::customsize:
                    //обычное окно, произвольный размер
                    if (rect.w > screensize.w) {
                        rect.w = screensize.w;
                        rect.x = 0;
                    }
                    else {
                        rect.x = (screensize.w - rect.w) / 2;
                    }
                    if (rect.h > screensize.h) {
                        rect.h = screensize.h;
                        rect.y = 0;
                    }
                    else {
                        rect.y = (screensize.h - rect.h) / 2;
                    }
                    sw_type = SW_NORMAL;
                    HWNDStyle |= WS_BORDER;
                    HWNDStyle |= WS_DLGFRAME;
                    HWNDStyle |= WS_THICKFRAME;
                    HWNDStyleEx |= WS_EX_WINDOWEDGE;
                    SetWindowLong(hwnd, GWL_STYLE, HWNDStyle | WS_POPUP);
                    SetWindowLong(hwnd, GWL_EXSTYLE, HWNDStyleEx | WS_EX_TOPMOST);
                    MoveWindow(hwnd, rect.x, rect.y, rect.w, rect.h, TRUE);
                    break;
            }
        }
        HWND window::gethwnd() {
            return hwnd;
        }
        LRESULT window::winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
            LRESULT lr = DefWindowProc(hwnd, msg, wparam, lparam);
            std::vector<function::basicfunction*>* procs = (std::vector<function::basicfunction*>*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (procs) {
                std::vector<void*> data{ &lr, &hwnd, &msg, &wparam, &lparam };
                uint64_t errorcode = 0;
                for (function::basicfunction* f : *procs) {
                    f->execute(&data, &errorcode, false, nullptr);
                    if (!errorcode) {
                        break;
                    }
                }
            }
            return lr;
        }
        HRESULT window::initwin(
            HWND& hwnd, 
            HINSTANCE hinstance, 
            std::wstring classname, 
            std::wstring title, 
            HICON hicon, HCURSOR 
            hcursor, 
            window_xywh rect
        ) {
            //Регистрация окна
            WNDCLASSEX wcex{
                sizeof(WNDCLASSEX),         //cbSize
                CS_HREDRAW | CS_VREDRAW,    //style
                winproc,                    //lpfnWndProc
                0,                          //cbClsExtra
                0,                          //cbWndExtra
                hinstance,                  //hInstance
                hicon,                      //hIcon
                hcursor,                    //hCursor
                (HBRUSH)(COLOR_WINDOW),     //hbrBackground
                NULL,                       //lpszMenuName
                classname.c_str(),          //lpszClassName
                hicon                       //hIconSm
            };
            if (!RegisterClassEx(&wcex)) return E_FAIL;
            //Создание окна
            hwnd = CreateWindow(
                classname.c_str(), 
                title.c_str(), 
                WS_OVERLAPPEDWINDOW, 
                rect.x, 
                rect.y, 
                rect.w, 
                rect.h, 
                NULL, 
                NULL, 
                hinstance, 
                NULL
            );
            if (!hwnd) return E_FAIL;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)&winsubproc);
            return S_OK;
        }
	}
}
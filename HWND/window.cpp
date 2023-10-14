#include "pch.h"
#include "window.h"
#include <iostream>
LRESULT deletewindow(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    return S_OK;
}
using namespace tokenoperator::dte_token::data;
using namespace tokenoperator::dte_token::stream;
using namespace tokenoperator::dte_token::function;
namespace win {
    namespace function {






        /*
        void create_win::execute(basic_stream& caller, bf_args& args, bool forced) {
            bf_args values(args, defaultvalues);
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



        void create_msg_loop::execute(basic_stream& caller, bf_args& args, bool forced) {
            if (!errorcodepointer) {
                return;		//avoid uncontrollable execution
            }
            std::vector<void*> values;
            filldefaultvalues(argumentspointer, values);
            MSG msg = { 0 };
            while (WM_QUIT != msg.message) {
                if (PeekMessage(&msg, *(HWND*)values[0], 0, 0, *(UINT*)values[2], PM_REMOVE)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else if (values[3]) {
                    ((basicfunction*)values[3])->execute(argumentspointer, errorcodepointer, forced, stream);
                    if (HAS_E) {
                        return;
                    }
                }
            }
        }
        */
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
        std::vector<basic_function*> winsubproc,
        HRESULT& hresult
    ) : rect(new window_xywh()), winsubproc(winsubproc){
        *(this->rect) = rect;
        hresult = initwin(
            hwnd,
            NULL,
            classname,
            title,
            hicon,
            hcursor,
            rect
        );
        if (!hresult) {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)&winsubproc);
        }
    }

    void window::update() {
        LONG HWNDStyle = GetWindowLong(hwnd.get_pointer(), GWL_STYLE);
        LONG HWNDStyleEx = GetWindowLong(hwnd.get_pointer(), GWL_EXSTYLE);
        window_xywh screensize = getscreensize();
        switch (show_mode->get_value()) {
            case window_showmode::FULLSCREEN:
                //полноэкранный режим
                sw_type = SW_MAXIMIZE;
                HWNDStyle &= ~WS_BORDER;
                HWNDStyle &= ~WS_DLGFRAME;
                HWNDStyle &= ~WS_THICKFRAME;
                HWNDStyleEx &= ~WS_EX_WINDOWEDGE;
                SetWindowLong(hwnd.get_pointer(), GWL_STYLE, HWNDStyle | WS_POPUP);
                SetWindowLong(hwnd.get_pointer(), GWL_EXSTYLE, HWNDStyleEx | WS_EX_TOPMOST);
                MoveWindow(hwnd.get_pointer(), 0, 0, screensize.get_value()[2], screensize.get_value()[3], TRUE);
                break;
            case window_showmode::CUSTOMSIZE:
                //обычное окно, произвольный размер
                if (rect->get_value()[2] > screensize.get_value()[2]) {
                    rect->get_value()[2] = screensize.get_value()[2];
                    rect->get_value()[0] = 0;
                }
                else {
                    rect->get_value()[0] = (screensize.get_value()[2] - rect->get_value()[2]) / 2;
                }
                if (rect->get_value()[3] > screensize.get_value()[3]) {
                    rect->get_value()[3] = screensize.get_value()[3];
                    rect->get_value()[1] = 0;
                }
                else {
                    rect->get_value()[1] = (screensize.get_value()[3] - rect->get_value()[3]) / 2;
                }
                sw_type = SW_NORMAL;
                HWNDStyle |= WS_BORDER;
                HWNDStyle |= WS_DLGFRAME;
                HWNDStyle |= WS_THICKFRAME;
                HWNDStyleEx |= WS_EX_WINDOWEDGE;
                SetWindowLong(hwnd.get_pointer(), GWL_STYLE, HWNDStyle | WS_POPUP);
                SetWindowLong(hwnd.get_pointer(), GWL_EXSTYLE, HWNDStyleEx | WS_EX_TOPMOST);
                MoveWindow(hwnd.get_pointer(), rect->get_value()[0], rect->get_value()[1], rect->get_value()[2], rect->get_value()[3], TRUE);
                break;
        }
    }
    LRESULT window::winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        LRESULT lr = DefWindowProc(hwnd, msg, wparam, lparam);
        std::vector<basic_function*>* procs = (std::vector<basic_function*>*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        /*if (procs) {
            std::vector<void*> data{ &lr, &hwnd, &msg, &wparam, &lparam };
            uint64_t errorcode = 0;
            for (basic_function* f : *procs) {
                f->execute(&data, &errorcode, false, nullptr);
                if (!errorcode) {
                    break;
                }
            }
        }
        */
        return lr;
    }
    HRESULT window::initwin(
        window_hwnd_p& hwnd,
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
            rect.get_value()[0], 
            rect.get_value()[1],
            rect.get_value()[2],
            rect.get_value()[3],
            NULL, 
            NULL, 
            hinstance, 
            NULL
        );
        if (!hwnd) return E_FAIL;
        return S_OK;
    }
}
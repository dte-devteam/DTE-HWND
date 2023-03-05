#include "pch.h"
#include "winproc.h"
namespace functions {
	namespace winproc {
		void post_quit::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if (*(UINT*)(*argumentspointer)[2] == WM_DESTROY) {
				PostQuitMessage(errorcodepointer ? *errorcodepointer : 0);
			}
		}
		void paint_handler::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if (*(UINT*)(*argumentspointer)[2] == WM_PAINT) {
				PAINTSTRUCT ps;
				HWND hwnd = *(HWND*)(*argumentspointer)[1];
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
			}
		}
	}
}
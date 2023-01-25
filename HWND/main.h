#pragma once
#include "window.h"
namespace functions {
	namespace win {
		inline std::vector<basicfunction*>* dllfunctions = new std::vector<basicfunction*>(
			{
				&get_screen_size,
				&create_window,
				&set_window_x,
				&set_window_y,
				&set_window_w,
				&set_window_h,
				&set_window_v,
				&set_window_sm,
				&get_window_hwnd,
				&create_window_message_loop
			}
		);
		std::vector<basicfunction*>* getfunctions() {
			return dllfunctions;
		}
	}
}
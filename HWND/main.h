#pragma once
#include "window.h"
#include "module/include/function_data.h"
#include "module/module_defines.h"
namespace functions {
	namespace win {
		//module functions
		std::vector<function::basicfunction*> dllfunctions{
			&get_screen_size,
			&create_window,
			&set_window_x,
			&set_window_y,
			&set_window_w,
			&set_window_h,
			&set_window_v,
			&set_window_sm,
			&get_window_hwnd,
			&create_window_message_loop,

			&winproc::win_post_quit,
			&winproc::win_paint_handler
		};
		//*****************new function export*******************
		//module has no dependencies, so function has empty reqirements ({ basicfunction* })
		DTE_EXPORTS std::vector<module::function_data> functions{
			{ &get_screen_size				},
			{ &create_window				},
			{ &set_window_x					},
			{ &set_window_y					},
			{ &set_window_w					},
			{ &set_window_h					},
			{ &set_window_v					},
			{ &set_window_sm				},
			{ &get_window_hwnd				},
			{ &create_window_message_loop	},
			{ &winproc::win_post_quit		},
			{ &winproc::win_paint_handler	}
		};
		//export functions
		DTE_EXPORTS std::vector<function::basicfunction*>* getfunctions() {
			return &dllfunctions;
		}
	}
}
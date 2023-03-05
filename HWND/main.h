#pragma once
#include "window.h"
#include "winproc.h"
#include "module/include/dependency_desc.h"
using namespace dependency_desc;
namespace functions {
	namespace win {
		//module functions
		static std::vector<basicfunction*>* dllfunctions = new std::vector<basicfunction*>{
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
		//module has no dependencies, so function has empty reqirements ({ basicfunction*, {} })
		static std::vector<function_data>* ndllfunctions = new std::vector<function_data>{
			{ &get_screen_size,				{} },
			{ &create_window,				{} },
			{ &set_window_x,				{} },
			{ &set_window_y,				{} },
			{ &set_window_w,				{} },
			{ &set_window_h,				{} },
			{ &set_window_v,				{} },
			{ &set_window_sm,				{} },
			{ &get_window_hwnd,				{} },
			{ &create_window_message_loop,	{} },
			{ &winproc::win_post_quit,		{} },
			{ &winproc::win_paint_handler,	{} }
		};
		//export functions
		std::vector<basicfunction*>* getfunctions() {
			return dllfunctions;
		}
	}
}
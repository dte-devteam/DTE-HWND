#pragma once
#pragma warning(disable:4275) //solve this later!
#include "pch.h"
#include "function/include/functionfactory.h"
#include "function/include/defaultvalues.h"
#include "token_data.h"
#include <string>
#define DEFAULT_CURSOR LoadCursor(NULL, IDC_ARROW)
#define DEFAULT_ICON LoadIcon(NULL, IDI_APPLICATION)
using namespace functionfactory;
namespace functions {
	struct screen_size : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct create_win : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_x : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_y : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_w : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_h : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_v : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_sm : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct get_win_hwnd : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct create_msg_loop : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};


	struct add_win_subproc : basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	namespace win {
		struct window_xywh {
			static void destruct(void* pointer);
			int x = 0, y = 0, w = 0, h = 0;
		};
		static const window_xywh default_xywh{ 0, 0, 500, 500 };
		enum windowshowmode {
			fullscreen,
			customsize
		};
		window_xywh getscreensize();
		class window {
			public:
				static void destruct(void* pointer);
				window(
					HINSTANCE hinstance,
					std::wstring classname, 
					std::wstring title, 
					HICON hicon, 
					HCURSOR hcursor, 
					window_xywh rect,
					std::vector<basicfunction*> winsubproc
				);
				void setX(int xpos);
				void setY(int ypos);
				void setW(int wpos);
				void setH(int hpos);
				void setV(bool visible);
				void setshowmode(int mode);
				window_xywh* get_xywh();
				bool getV();
				std::vector<basicfunction*> winsubproc;
				HWND gethwnd();
			protected:
				virtual ~window() {}
				HRESULT condition;
			private:
				int sw_type = SW_NORMAL; //SW_HIDE;
				bool visible = true;
				int showmode = windowshowmode::customsize;
				window_xywh rect;
				HWND hwnd;
				std::wstring classname;
				static LRESULT CALLBACK winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
				HRESULT initwin(
					HWND& hwnd, 
					HINSTANCE hinstance, 
					std::wstring classname, 
					std::wstring title, 
					HICON hicon, 
					HCURSOR hcursor,
					window_xywh rect
				);
		};
	}
	static screen_size get_screen_size{
		token_data::token_name_to_id(L"get_screen_size")	//name
	};
	static create_win create_window{
		token_data::token_name_to_id(L"create_window"),	//name
		{	//default values
			nullptr,
			nullptr,
			(void*)new std::wstring(L"NO_NAME_WINDOW"),
			(void*)new std::wstring(L"NO_TITLE_WINDOW"),
			(void*)DEFAULT_ICON,
			(void*)DEFAULT_CURSOR,
			(void*)&win::default_xywh,
			(void*)new std::vector<basicfunction*>()
		}
	};
	static set_win_x set_window_x{
		token_data::token_name_to_id(L"set_window_x")	//name
	};
	static set_win_y set_window_y{
		token_data::token_name_to_id(L"set_window_y")	//name
	};
	static set_win_w set_window_w{
		token_data::token_name_to_id(L"set_window_w")	//name
	};
	static set_win_h set_window_h{
		token_data::token_name_to_id(L"set_window_h")	//name
	};
	static set_win_v set_window_v{
		token_data::token_name_to_id(L"set_window_v")	//name
	};
	static set_win_sm set_window_sm{
		token_data::token_name_to_id(L"set_window_sm")	//name
	};
	static get_win_hwnd get_window_hwnd{
		token_data::token_name_to_id(L"get_window_hwnd")	//name
	};
	static create_msg_loop create_window_message_loop{
		token_data::token_name_to_id(L"create_window_message_loop"),	//name
		{	//default values
			(void*)&defaultvalues::NULL_PTR,
			(void*)&defaultvalues::UINT_ZERO,
			(void*)&defaultvalues::UINT_ZERO,
			nullptr
		}
	};
}
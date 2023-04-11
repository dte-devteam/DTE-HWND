#pragma once
#pragma warning(disable:4275) //solve this later!
#include "pch.h"
#include "function/include/basicfunction.h"
#include "data/include/values.h"
#include "data/include/errorvalues.h"
#include "token_data.h"
#include "winproc.h"
#include <string>
#define DEFAULT_CURSOR LoadCursor(NULL, IDC_ARROW)
#define DEFAULT_ICON LoadIcon(NULL, IDI_APPLICATION)
namespace functions {
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
				std::vector<function::basicfunction*> winsubproc
			);
			void setX(int xpos);
			void setY(int ypos);
			void setW(int wpos);
			void setH(int hpos);
			void setV(bool visible);
			void setshowmode(int mode);
			window_xywh* get_xywh();
			bool getV();
			std::vector<function::basicfunction*> winsubproc;
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
	//constructors
	struct screen_size : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct create_win : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_x : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_y : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_w : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_h : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_v : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct set_win_sm : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct get_win_hwnd : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	struct create_msg_loop : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};


	struct add_win_subproc : function::basicfunction {
		using basicfunction::basicfunction;
		void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
	};
	//instances
	inline screen_size get_screen_size{
		token_data::token_name_to_id(L"get_screen_size"),	//function name
		{	//default values
			nullptr		//pointer where save win::window_xywh
		}
	};
	inline create_win create_window{
		token_data::token_name_to_id(L"create_window"),	//function name
		{	//default values
			nullptr,															//pointer where save win::window
			nullptr,															//HINSTANCE (has same sise as ponter)
			(void*)new std::wstring(L"NO_NAME_WINDOW"),							//pointer to set window class name
			(void*)new std::wstring(L"NO_TITLE_WINDOW"),						//pointer to set window title
			(void*)DEFAULT_ICON,												//HICON (has same sise as ponter)									
			(void*)DEFAULT_CURSOR,												//HCURSOR (has same sise as ponter)
			(void*)&win::default_xywh,											//pointer to set window position and size
			(void*)new std::vector<function::basicfunction*>({ &winproc::win_post_quit })	//pointer to set window window processes
		}
	};
	inline set_win_x set_window_x{
		token_data::token_name_to_id(L"set_window_x")	//function name
	};
	inline set_win_y set_window_y{
		token_data::token_name_to_id(L"set_window_y")	//function name
	};
	inline set_win_w set_window_w{
		token_data::token_name_to_id(L"set_window_w")	//function name
	};
	inline set_win_h set_window_h{
		token_data::token_name_to_id(L"set_window_h")	//function name
	};
	inline set_win_v set_window_v{
		token_data::token_name_to_id(L"set_window_v")	//function name
	};
	inline set_win_sm set_window_sm{
		token_data::token_name_to_id(L"set_window_sm")	//function name
	};
	inline get_win_hwnd get_window_hwnd{
		token_data::token_name_to_id(L"get_window_hwnd"),	//function name
		{	//default values
			nullptr,	//pointer of win::window
			nullptr		//pointer where save HWND
		}
	};
	inline create_msg_loop create_window_message_loop{
		token_data::token_name_to_id(L"create_window_message_loop"),	//function name
		{	//default values
			(void*)&data::NULL_PTR,
			(void*)&data::UINT_ZERO,
			(void*)&data::UINT_ZERO,
			nullptr
		}
	};
}
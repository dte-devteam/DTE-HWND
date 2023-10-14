#pragma once
#pragma warning(disable:4275) //solve this later!
#include "pch.h"
#include "winproc.h"
#include <vector>
#define DEFAULT_CURSOR LoadCursor(NULL, IDC_ARROW)
#define DEFAULT_ICON LoadIcon(NULL, IDI_APPLICATION)
namespace win {
	typedef tokenoperator::dte_token::data::value<int[4]> window_xywh;
	typedef tokenoperator::dte_token::data::value<int> window_sm;
	typedef tokenoperator::dte_token::data::value<bool> window_v;
	typedef tokenoperator::dte_token::data::smart_pointer<window_xywh> window_xywh_p;
	typedef tokenoperator::dte_token::data::smart_pointer<window_sm> window_sm_p;
	typedef tokenoperator::dte_token::data::smart_pointer<window_v> window_v_p;
	typedef tokenoperator::dte_token::data::smart_pointer<HWND__> window_hwnd_p;
	enum window_showmode {
		FULLSCREEN,
		CUSTOMSIZE
	};
	window_xywh getscreensize();
	class window {
		public:
			window(
				HINSTANCE hinstance,
				std::wstring classname,
				std::wstring title,
				HICON hicon,
				HCURSOR hcursor,
				window_xywh rect,
				std::vector<tokenoperator::dte_token::function::basic_function*> winsubproc,
				HRESULT& hresult
			);
			virtual ~window() {}
			void update();
			window_v_p visible = new window_v(true);
			window_sm_p show_mode = new window_sm(CUSTOMSIZE);
			window_xywh_p rect;
			std::vector<tokenoperator::dte_token::function::basic_function*> winsubproc;
		protected:
			int sw_type = SW_NORMAL; //SW_HIDE;
			window_hwnd_p hwnd;
			static LRESULT CALLBACK winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
			static HRESULT initwin(
				window_hwnd_p& hwnd,
				HINSTANCE hinstance,
				std::wstring classname,
				std::wstring title,
				HICON hicon,
				HCURSOR hcursor,
				window_xywh rect
			);
	};
	namespace function {
		struct create_win : tokenoperator::dte_token::function::basic_function {
			using tokenoperator::dte_token::function::basic_function::basic_function;
			void execute(tokenoperator::dte_token::stream::basic_stream& caller, tokenoperator::dte_token::function::bf_args& args, bool forced = false);
		};
		


		struct create_msg_loop : tokenoperator::dte_token::function::basic_function {
			using tokenoperator::dte_token::function::basic_function::basic_function;
			void execute(tokenoperator::dte_token::stream::basic_stream& caller, tokenoperator::dte_token::function::bf_args& args, bool forced = false);
		};


		struct add_win_subproc : tokenoperator::dte_token::function::basic_function {
			using tokenoperator::dte_token::function::basic_function::basic_function;
			void execute(tokenoperator::dte_token::stream::basic_stream& caller, tokenoperator::dte_token::function::bf_args& args, bool forced = false);
		};



		//friend win func
		bool& get_V();
		void set_showmode(int mode);
		window_xywh_p get_xywh();
		std::vector<tokenoperator::dte_token::function::basic_function*> winsubproc;
		//HWND gethwnd(); is realy needed?
	}
}
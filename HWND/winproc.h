#pragma once
#include "function/include/functionfactory.h"
#include "data/include/values.h"
#include "token_data.h"
using namespace functionfactory;
namespace functions {
	namespace winproc {
		//constructors
		struct post_quit : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct paint_handler : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		//instances
		static post_quit* win_post_quit = new post_quit(
			token_data::token_name_to_id(L"win_post_quit")	//name
		);
		static paint_handler* win_paint_handler = new paint_handler(
			token_data::token_name_to_id(L"win_paint_handler")	//name
		);
	}
}
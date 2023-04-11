#pragma once
#include "function/include/basicfunction.h"
#include "data/include/values.h"
#include "token_data.h"
namespace functions {
	namespace winproc {
		//constructors
		struct post_quit : function::basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct paint_handler : function::basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		//instances
		inline post_quit win_post_quit{
			token_data::token_name_to_id(L"win_post_quit")	//name
		};
		inline paint_handler win_paint_handler{
			token_data::token_name_to_id(L"win_paint_handler")	//name
		};
	}
}
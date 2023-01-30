#pragma once
#include "function/include/functionfactory.h"
#include "function/include/defaultvalues.h"
#include "token_data.h"
using namespace functionfactory;
namespace functions {
	namespace winproc {
		struct post_quit : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};

		static post_quit win_post_quit{
			token_data::token_name_to_id(L"win_post_quit")	//name
		};
	}
}
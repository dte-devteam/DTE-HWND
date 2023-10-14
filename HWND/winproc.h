#pragma once
#include "token/stream/include/basic_stream.h"
#include "token/function/error_codes.h"
#include "token/data/include/value.h"
namespace functions {
	namespace winproc {
		struct post_quit : tokenoperator::dte_token::function::basic_function {
			using tokenoperator::dte_token::function::basic_function::basic_function;
			void execute(tokenoperator::dte_token::stream::basic_stream& caller, tokenoperator::dte_token::function::bf_args& args, bool forced = false);
		};
		struct paint_handler : tokenoperator::dte_token::function::basic_function {
			using tokenoperator::dte_token::function::basic_function::basic_function;
			void execute(tokenoperator::dte_token::stream::basic_stream& caller, tokenoperator::dte_token::function::bf_args& args, bool forced = false);
		};
	}
}
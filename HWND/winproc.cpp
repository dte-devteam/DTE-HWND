#include "pch.h"
#include "winproc.h"
namespace functions {
	namespace winproc {
		void post_quit::execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
			if (*(UINT*)(*argumentspointer)[2] == WM_DESTROY) {
				PostQuitMessage(errorcodepointer ? *errorcodepointer : 0);
			}
		}
	}
}
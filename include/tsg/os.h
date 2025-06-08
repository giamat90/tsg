#include "tsg.h"
#include <filesystem>

#ifdef _WIN32
	#include <windows.h>
#elif defined(__linux__)
	#include <unistd.h>
	#include <limits.h>
#elif defined(__APPLE__)
	#include <mach-o/dyld.h>
	#include <limits.h>
#endif

namespace tsg {
	class TSG_API os {
	public:
		static std::filesystem::path get_exe_path();
	};
}
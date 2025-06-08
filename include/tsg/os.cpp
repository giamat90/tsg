#include "os.h"

namespace tsg {
	std::filesystem::path os::get_exe_path() {
#ifdef _WIN32
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        std::filesystem::path exe_path(buffer);
        return exe_path.parent_path();
#elif defined(__linux__)
        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
        if (count != -1) {
            std::filesystem::path exe_path(std::string(buffer, count));
            return exe_path.parent_path();
        }
        return {};
#elif defined(__APPLE__)
        char buffer[PATH_MAX];
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) == 0) {
            std::filesystem::path exe_path(buffer);
            return exe_path.parent_path();
        }
        return {};
#else
    #error "Unsupported platform"
#endif
	}
}
#include "os.h"
#include <fstream>
#include <assert.h>

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

    file::file(const std::filesystem::path& p, const TYPE t) : m_type(t) 
    {
        m_file.clear();
        switch (m_type)
        {
        case tsg::file::TYPE::WR:
            m_file.open(p.string(), std::ios::out);
            if (m_file.is_open()) {
                m_file.close();
                m_file.open(p.string(), std::ios::in | std::ios::out);
            }
            break;
        case tsg::file::TYPE::WO:
            m_file.open(p.string(), std::ios::out);
            break;
        case tsg::file::TYPE::RO:
            m_file.open(p.string(), std::ios::in);
            break;
        default:
            m_file.open(p.string(), std::ios::binary);
            break;
        }
        assert(m_file.is_open());
    }
    file::~file() {
        m_file.close();
    }

    void read() {
        /* TODO */
    }

    void file::write(const std::string& s) {
        m_file << s;
    }

    void file::write_line(const std::string& s) {
        m_file << s << std::endl;
    }
}
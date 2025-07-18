#include "os.h"
#include <fstream>
#include <assert.h>

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

    tsg::string date::get_date(const TYPE t, const bool endline) {
        tsg::string ret{};
        /*
        * ctime_s return a date in this format
        * "DDD MMM  D HH:MM:SS YYYY\n"
        */
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        switch (t)
        {
        case(TYPE::FULL_DATE):
            if (endline) {
                ret = buffer;
            }
            else {
                ret = std::string(buffer, size_t(24));
            }
            break;
        case(TYPE::ONLY_DATE):
            if (endline) {                
                buffer[7] = '\n';
                ret = std::string(buffer, size_t(8));
            }
            else {
                ret = std::string(buffer, size_t(7));
            }
            break;
        case(TYPE::ONLY_TIME):
            if (endline) {
                buffer[19] = '\n';
                ret = std::string(buffer + 11, size_t(9));
            }
            else {
                ret = std::string(buffer + 11, size_t(8));
            }
            break;
        default:
            break;
        }
        return ret;
    }

    class file::impl : public std::fstream {};

    file::file(const std::filesystem::path& p, const TYPE t) : m_type(t) 
    {
        m_file = new impl();
        m_file->exceptions(std::ifstream::failbit | std::ifstream::badbit); // enabling exceptions
        m_file->clear();
        switch (m_type)
        {
        case tsg::file::TYPE::WR:
            m_file->open(p.string(), std::ios::out);
            if (m_file->is_open()) {
                m_file->close();
                m_file->open(p.string(), std::ios::in | std::ios::out);
            }
            break;
        case tsg::file::TYPE::WO:
            m_file->open(p.string(), std::ios::out);
            break;
        case tsg::file::TYPE::RO:
            m_file->open(p.string(), std::ios::in);
            break;
        default:
            m_file->open(p.string(), std::ios::binary);
            break;
        }
        assert(m_file->is_open());
    }
    
    file::~file() {
        m_file->close();
        delete m_file;
    }

    void file::read() {
        /* TODO */
        throw;
    }

    void file::write(const std::string& s) {
        *m_file << s;
    }

    void file::write_line(const std::string& s) {
        *m_file << s << std::endl;
    }
}
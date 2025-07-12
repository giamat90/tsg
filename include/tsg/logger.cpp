#if 1
#include "logger.h"
#include <chrono>
#include <ctime>

namespace tsg {

	template class TSG_API singleton<logger>;

	logger::logger(const std::string& file_name, const bool use_time) : m_file(tsg::os::get_exe_path() / file_name), m_use_time(use_time) {}

	logger::~logger() {}

	void logger::write(const tsg::string& s) {
		std::string log{};
		if (m_use_time) {
			auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			char buffer[26];
			ctime_s(buffer, sizeof(buffer), &now);
			buffer[24] = ' ';	// replace '\n' with a space ' '
			log += buffer;

		}
		log += s;
		m_file.write_line(log);
	}
}
#endif
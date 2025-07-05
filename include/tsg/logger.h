#pragma once

#include "tsg.h"
#include "types.h"
#include "os.h"
#include "string.h"

namespace tsg {
	class TSG_API logger : public tsg::singleton<logger> {
	public:
		logger(const std::string& file_name = "log.txt", const bool use_time = true);

		~logger();

		void write(const tsg::string& s);

		template <typename ...Args>
		void write(Args... args) {
			write(tsg::string(args...));
		};

		inline void use_time(const bool b) { m_use_time = b; }
	private:
		tsg::file m_file;
		bool m_use_time{ false };
	};
}
#include "tsg.h"
#include <filesystem>
#include <fstream>

namespace tsg {
	class TSG_API os {
	public:
		static std::filesystem::path get_exe_path();
	};

	class TSG_API file {
	public:
		enum class TYPE {
			WR,
			WO,
			RO
		};
	public:
		file(const std::filesystem::path& p, const TYPE t = TYPE::WR);
		~file();
		void read();
		void write(const std::string& s);
		void write_line(const std::string& s);
	private:
		class impl;
		impl* m_file;
		//std::fstream m_file;
		TYPE m_type{ TYPE::WR };
	};
}
#include <fstream>
#include <string>
#include "types.hpp"

namespace Config {
	
	/// Class for config file manipulation
	class Config {
	private:
		json config;
		std::ifstream config_file;
		~Config();
	public:
		json config;
		Config (const std::string config_file_path);
	}

		std::string
	get_token_from_credentials (const std::string &user, const std::string &password);
}

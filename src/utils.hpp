#include <fstream>
#include <string>
#include "cpr/cprtypes.h"
#include "types.hpp"
#include <cpr/cpr.h>

string
OAUTH_URL = "https://oauth.yandex.ru/token",
API_URL = "https://api.music.yandex.net";

struct _client_data_{
	CLIENT_ID = "23cabbbdc6cd418abb4b39c32c41195d",
	CLIENT_SECRET = "53bc75238f0c4d08a118e51fe9203300",
	
} client_data;

class
request_headers{
public:
	cpr::Header
	request_headers(const &string token, const string &language);
};

class Request {
public:
	static json request_api(const string &endpoint, cpr::Headers headers);
	static future_json async_request_api(string endpoint, cpr::Headers headers);
}

/// Class for config file manipulation
class Config {
private:
	json config;
	std::ifstream config_file;
	~Config();
public:
	json config;
	Config (const string &config_file_path);
}

string
GetTokenFromCredentials (const string &user, const string &password);


#include "cpr/cprtypes.h"
#include "types.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <string>
#include <cstdlib>

const string
	OAUTH_URL = "https://oauth.yandex.ru/token",
	API_URL = "https://api.music.yandex.net",
	HOME_PATH = std::getenv("HOME");

const struct _client_data_ {
  string CLIENT_ID = "23cabbbdc6cd418abb4b39c32c41195d",
         CLIENT_SECRET = "53bc75238f0c4d08a118e51fe9203300";

} client_data;

cpr::Header request_headers(const string &token, const string &language);

class Request {
public:
  static json request_api(const string &endpoint, cpr::Header headers);
  static future_json async_request_api(const string &endpoint, cpr::Header headers);
};

/// Class for config file manipulation
class Config {
private:
  std::ifstream config_file;
  ~Config();

public:
  json config;
	Config(const string &config_file_path = HOME_PATH + "./config/config.json");
};

string GetTokenFromCredentials(const string &user, const string &password);

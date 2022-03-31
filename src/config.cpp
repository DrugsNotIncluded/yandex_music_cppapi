#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include "cpr/cpr.h"
#include "types.hpp"
#include "config.hpp"

namespace Config {
	
	Config::Config(const std::string config_file_path = std::getenv("HOME")+"./config/config.json") {
		this->config_file = std::ifstream::open(config_file_path);
		this->config = json::parse(config_file);
	}

	Config::~Config() {
		config_file.close();
	}

	std::string
	get_token_from_credentials (const std::string &user, const std::string &password) {	
		cpr::Url url = cpr::Url{oauth_url};
		cpr::Session session;
		session.SetOption(url);
		session.PreparePost();
		session.SetPayload(cpr::Payload{{"grant_type", "password"},
										{"client_id", CLIENT_ID},
										{"client_secret", CLIENT_SECRET},
										{"username", user},
										{"password", password}});

		auto session_handle = session.GetCurlHolder()->handle;
		curl_easy_setopt(session_handle, CURLOPT_ACCEPT_ENCODING, NULL);
		CURLcode curl_result = curl_easy_perform(session_handle);
		cpr::Response r = session.Complete(curl_result);
	
		std::cerr << r.error.message << std::endl;

		json response = json::parse(r.text);
		std::string token = response["access_token"];
	
		return token;
	}
}

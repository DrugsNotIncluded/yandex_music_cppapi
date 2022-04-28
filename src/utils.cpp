#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include <fmt/format.h>
#include "cpr/cpr.h"
#include "cpr/cprtypes.h"
#include "types.hpp"
#include "utils.hpp"

cpr::Header
request_headers::request_headers(const string &token, const string &language) {
	return cpr::Header{{"X-Yandex-Music-Client","YandexMusicAndroid/23020251"},
								{"User-Agent","Yandex-Music-API"},
								{"Connection","Keep-Alive"},
								{"Authorization",fmt::format("OAuth {}",token)},
								{"Accept-Language",language}};
}

json
Request::request_api(const string &endpoint, cpr::Headers headers) {
	cpr::Response r = cpr::Get(cpr::Url{API_URL+endpoint}, headers);
	std::cerr << r.error.message << std::endl;
	json response = json::parse(r.text);
	return response;
}

future_json
Request::async_request_api(const string &endpoint, cpr::Headers headers) {
	auto future_response = cpr::GetCallback([](cpr::Response r) {
		return json::parse(r.text);
	}, cpr::Url{API_URL+endpoint}, headers);
	return future_response;}

Config::Config(const string &config_file_path = std::getenv("HOME")+"./config/config.json") {
	this->config_file = std::ifstream::open(config_file_path);
	this->config = json::parse(config_file);
}

Config::~Config() {
	config_file.close();
}

string
GetTokenFromCredentials (const string &user, const string &password) {	
	cpr::Url url = cpr::Url{oauth_url};
	cpr::Session session;
	session.SetOption(url);
	session.PreparePost();
	session.SetPayload(cpr::Payload{{"grant_type", "password"},
									{"client_id",client_data.CLIENT_ID},
									{"client_secret", client_data.CLIENT_SECRET},
									{"username", user},
									{"password", password}});

	auto session_handle = session.GetCurlHolder()->handle;
	curl_easy_setopt(session_handle, CURLOPT_ACCEPT_ENCODING, NULL);
	CURLcode curl_result = curl_easy_perform(session_handle);
	cpr::Response r = session.Complete(curl_result);
	
	std::cerr << r.error.message << std::endl;

	json response = json::parse(r.text);
	string token = response["access_token"];
	
	return token;
}

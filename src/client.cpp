#include "cpr/api.h"
#include "cpr/auth.h"
#include "cpr/cpr.h"
#include "cpr/cprtypes.h"
#include "cpr/curl_container.h"
#include "cpr/parameters.h"
#include "cpr/payload.h"
#include "cpr/response.h"
#include "cpr/session.h"
#include "cpr/ssl_options.h"
#include "curl/curl.h"
#include "curl/easy.h"
#include <cstdio>
#include <cstring>
#include <iterator>
#include <ostream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "client.hpp"
#include <fmt/format.h>
#include <vector>
#include <future>
#include <fstream>
#include "config.hpp"
#include "types.hpp"

Client::Client(const std::string &token, const std::string &language) {
	this->token = token;
	this->language = language;
	this->headers = cpr::Header{{"X-Yandex-Music-Client","YandexMusicAndroid/23020251"},
								{"User-Agent","Yandex-Music-API"},
								{"Connection","Keep-Alive"},
								{"Authorization",fmt::format("OAuth {}",this->token)},
								{"Accept-Language",this->language}};

	this->user_data = this->get_account_status();
	this->user_id = user_data["result"]["account"]["uid"];
}

json
Client::request_api(std::string endpoint) {
	cpr::Response r = cpr::Get(cpr::Url{base_url+endpoint}, this->headers);
	std::cerr << r.error.message << std::endl;
	json response = json::parse(r.text);
	return response;
}

future_json
Client::async_request_api(std::string endpoint) {
	auto future_response = cpr::GetCallback([](cpr::Response r) {
		return json::parse(r.text);
	}, cpr::Url{base_url+endpoint}, this->headers);
	return future_response;}

future_json
Client::async_get_feed() {
	return this->async_request_api("/feed");}

json
Client::get_account_status() {
	return this->request_api("/account/status");}

future_json
Client::async_user_likes_tracks() {
	return this->async_request_api("/users/"+std::to_string(this->user_id)+"/likes/tracks");}

future_json
Client::async_user_settings() {
	return this->async_request_api("/account/settings");}

future_json_list
Client::async_tracks_download_info(json tracks_base_info) {
	future_json_list tracks_full_info{};
	for (auto it = tracks_base_info.begin(); it!=tracks_base_info.end(); ++it) {
		string track_id = it.value()["id"];
		tracks_full_info.emplace_back(async_request_api("/tracks/"+ track_id +"/download-info"));}
	return tracks_full_info;}

future_json
Client::async_track_supplement(int track_id) {
	return this->async_request_api("/tracks/"+std::to_string(track_id)+"/supplement");}

future_json
Client::async_track_similar(int track_id) {
	return this->async_request_api("/tracks/"+std::to_string(track_id)+"/similar");}
	

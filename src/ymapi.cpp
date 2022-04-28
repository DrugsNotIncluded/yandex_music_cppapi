#include <cpr/cpr.h>
#include <cpr/cprtypes.h>
#include <string>
#include "types.hpp"
#include "utils.hpp"
#include "ymapi.hpp"

Session::Session(const string &token, const string &language) {
	this->headers = request_headers(token, language);
	this->uid = this->get_account_status()["result"]["account"]["uid"];
}

json
Session::get_account_status() {
	return Request::request_api("/account/status", this->headers);
}

future_json
Session::async_get_feed() {
	return Request::async_request_api("/feed", this->headers);
}

future_json
Session::async_user_likes_tracks() {
	return Request::async_request_api("/users/" + this->uid + "/likes/tracks", this->headers);
}

future_json
Session::async_user_settings() {
	return Request::async_request_api("/account/settings", this->headers);
}

future_json
Session::async_track_supplement(int track_id) {
	return Request::async_request_api("/tracks/"+std::to_string(track_id)+"/supplement", this->headers);
}

future_json
Session::async_track_similar(int track_id) {
	return Request::async_request_api("/tracks/"+std::to_string(track_id)+"/similar")
}

future_json_list
Session::async_tracks_download_info(json tracks_base_info) {
	future_json_list tracks_full_info{};
	for (auto it = tracks_base_info.begin(); it!=tracks_base_info.end(); ++it) {
		string track_id = it.value()["id"];
		tracks_full_info.emplace_back(Request::async_request_api("/tracks/"+ track_id +"/download-info", this->headers));}
	return tracks_full_info;
}

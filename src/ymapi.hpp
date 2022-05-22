#ifndef YMAPI_H
#define YMAPI_H
#endif

#include <cpr/cpr.h>
#include "types.hpp"
#include "utils.hpp"

class Session {
private:
	cpr::Header headers;
	string uid;
public:
	Session(const string &token, const string &language);
	json get_account_status();
	future_json async_get_feed();
	future_json async_user_likes_tracks();
	future_json async_user_settings();
	future_json async_track_supplement(int track_id);
	future_json async_track_similar(int track_id);
	future_json_list async_tracks_download_info(json tracks_base_info);
};

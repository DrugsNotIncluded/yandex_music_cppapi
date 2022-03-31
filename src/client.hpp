#include "cpr/api.h"
#include "cpr/cprtypes.h"
#include "cpr/parameters.h"
#include "cpr/response.h"
#include "nlohmann/json.hpp"
#include <future>
#include <stdlib.h>
#include <string>
#include <vector>
#include "types.hpp"

const std::string
	CLIENT_ID = "23cabbbdc6cd418abb4b39c32c41195d",
	CLIENT_SECRET = "53bc75238f0c4d08a118e51fe9203300",
	/// Yandex music OAuth endpoint
	oauth_url = "https://oauth.yandex.ru/token";

class Client {
private:
	/// Yandex music API endpoint
	const std::string base_url = "https://api.music.yandex.net";
	std::string token, language;
	/// Unique user id
	int user_id;
	/// Json data object, contains user data
	json user_data;
	/// Headers required for requests to YM
	cpr::Header headers;
public:
	/// Main client class, provides API interaction tools
	Client(const std::string &token=nullptr, const std::string &language = "ru");
	/// Sync call to yandex music API
	json request_api(std::string endpoint);
	/// Get account info: active subscriptions, username, promo
	json get_account_status();
	/// Async call to yandex music API
	future_json async_request_api(std::string endpoint);
	/// Get user feed
	future_json async_get_feed();
	/// Get tracks liked by user
	future_json async_user_likes_tracks();
	/// Get user settings
	future_json async_user_settings();
	/// Get additional track info
	future_json async_track_supplement(int track_id);
	/// Get similar tracks
	future_json async_track_similar(int track_id);
	/// Get track liked by user (Async)
	future_json_list async_tracks_download_info(json tracks_data);
	
};

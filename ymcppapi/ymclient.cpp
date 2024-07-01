#include "ymclient.hpp"
#include "cpr/async_wrapper.h"
#include "cpr/parameters.h"
#include "cpr/payload.h"
#include "cpr/session.h"
#include <future>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
using PathParams = map<string, string>;

// https://stackoverflow.com/a/8581865
template<typename T>
string vector_to_comma_separated(const vector<T>& vec) {
    std::ostringstream oss;
    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
            std::ostream_iterator<int>(oss, ","));

        // Now add the last element with no delimiter
        oss << vec.back();
    }
    return (oss.str());
}

namespace ymapi {
    YMClient::YMClient(const string &token, const string &language) {
        this->client = new YMAPI(token, language);
    }

    // User

    AsyncJson
    YMClient::user_playlists(int uid) {
        PathParams params{{"uid",to_string(uid)}};
        return (this->client->ApiGET("/users/{userId}/playlists/list", params).value());
    }

    AsyncJson
    YMClient::user_dislikes_tracks(int uid) {
        PathParams params{{"uid",to_string(uid)}};
        return (this->client->ApiGET("/users/{userId}/dislikes/tracks", params).value());
    }

    AsyncJson 
    YMClient::user_playlist_bykind(int uid, int kind) {
        PathParams params = {{"uid",to_string(uid)}, {"kind", to_string(kind)}};
        return (this->client->ApiGET("/users/{userId}/playlists/{kind}",params).value());
    }

    AsyncJson
    YMClient::user_playlists_bykind(int uid, vector<int> kinds) {
        PathParams params {{"uid",to_string(uid)}};
        cpr::Parameters query{{"kinds", vector_to_comma_separated(kinds)}};
        return (this->client->ApiGET("/users/{userId}/playlists", params, query).value());
    }

    AsyncJson 
    YMClient::user_create_playlist(int uid, string title, bool visibility) {
        PathParams params{{"uid",to_string(uid)}};
        cpr::Payload data{{"title",title},{"visibility",to_string(visibility)}};
        return (this->client->ApiPOST("/users/{userId}/playlists/create", params, nullopt, data).value());
    }

    AsyncJson 
    YMClient::user_change_playlist_name(int uid, int kind, string title) {
        PathParams params{{"uid",to_string(uid)},{"kind",to_string(kind)}};
        cpr::Payload data{{"title",title}};
        return (this->client->ApiPOST("users/{userId}/playlists/{kind}/name", params, nullopt, data).value());
    }

    AsyncJson 
    YMClient::user_delete_playlist(int uid, int kind) {
        PathParams params{{"uid",to_string(uid)},{"kind",to_string(kind)}};
        return (this->client->ApiPOST("/users/{userId}/playlists/{kind}/delete",params).value());
    }

    AsyncJson 
    YMClient::user_add_tracks_to_playlist(int uid, int kind, map<int,int> &tracks) {
        PathParams params{{"uid",to_string(uid)},{"kind",to_string(kind)}};
        json diff = {{"op", "insert"},{"at", 0}, {"tracks", {}}};
        for (auto const& [key,val] : tracks) {
            diff["tracks"].push_back({{"id", to_string(key)},{"albumId", val}});
        }
        cpr::Payload data {{"diff",diff.dump()}};
        return (this->client->ApiPOST("/users/{userId}/playlists/{kind}/change-relative", params, nullopt, data).value());
    }

    // Account

    AsyncJson
    YMClient::account_status() {
        return (this->client->ApiGET("/account/status").value());
    }
}
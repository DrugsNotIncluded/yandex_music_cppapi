#include "nlohmann/json.hpp"
#include <functional>
#include <future>
#include <optional>
#include <string>
#include "ymapi.hpp"

using namespace std;
using json = nlohmann::json;

namespace ymapi {
    class YMClient {
        private:
            YMAPI* client;
        public:
        // User:
            YMClient(const string &token, const string &language);
            AsyncJson user_playlists(int uid);

            AsyncJson user_dislikes_tracks(int uid);

            AsyncJson user_playlist_bykind(int uid, int kind);

            AsyncJson user_playlists_bykind(int uid, vector<int> kinds);

            AsyncJson user_create_playlist(int uid, string title, bool visibility);

            AsyncJson user_change_playlist_name(int uid, int kind, string title);

            AsyncJson user_delete_playlist(int uid, int kind);

            AsyncJson user_add_tracks_to_playlist(int uid, int kind, map<int,int> &tracks);
            AsyncJson user_del_tracks_from_playlist(int uid, int kind, map<int,int> &tracks);

            AsyncJson user_get_recommendations_for_playlist(int uid, int kind);

            AsyncJson user_change_playlist_visibility(int uid, int kind, bool visibility);

            template<typename... Track>
            AsyncJson user_like_tracks(int uid, Track... track);

            template<typename... Track>
            AsyncJson user_dislike_tracks(int uid, Track... track);

            AsyncJson user_likes_tracks(int uid);

            template<typename... Track>
            AsyncJson user_remove_likes(int uid, Track... track);

        // Tracks:
            template<typename... Track>
            AsyncJson tracks_get(Track... track);

            AsyncJson track_download_info(int track_id);

            AsyncJson track_supplement(int track_id);

            AsyncJson track_similar(int track_id);

            AsyncJson track_lyrics(int track_id);

            //AsyncJson track_play_audio();
        // Albums:
            AsyncJson album_get(int album_id);

            AsyncJson album_get_with_tracks(int album_id);

            template<typename... AlbumID>
            AsyncJson albums_get(AlbumID... album_id);
        // Playlists:
            template<typename... IDPack>
            AsyncJson playlists_get(IDPack... uid_pack);

        // Landing:
            // И че это за хуета. Потом прикручу, далеко не самое важное

        // Artists:
            AsyncJson artist_popular_tracks(int artist_id);

            AsyncJson artist_brief_info(int artist_id);

            AsyncJson artist_tracks(int artist_id);

            AsyncJson artist_direct_albums(int artist_id);
        // Rotor:
            AsyncJson rotor_get_station_info(int station_id);

            AsyncJson rotor_get_station_tracks(int station_id);

            AsyncJson rotor_get_account_status();
            
            AsyncJson rotor_get_stations_list(const optional<reference_wrapper<string>> &language);

            AsyncJson rotor_get_dashboard();

            AsyncJson rotor_send_feedback(int station_id, const optional<reference_wrapper<int>> &batch_id);
        // Tags:
            AsyncJson tags_get_playlist_bytag(int tag_id);
        // Default:
            AsyncJson settings();
            AsyncJson permission_alerts();
            AsyncJson feed_wizard_is_passed();
            AsyncJson feed();
            AsyncJson genres();
            AsyncJson non_music_catalogue();
        // Account:
            AsyncJson account_experiments();
            AsyncJson account_consume_promo_code(const string& promo);
            AsyncJson account_get_settings();
            //AsyncJson account_set_settings();
            AsyncJson account_status();
        // Search:
            AsyncJson search(const string &text, const int &page_number = 0, const string &type = "all", const bool &nocorrect = false);
            AsyncJson search_suggest(const string &search_query_part);
        // Queues:
           //AsyncJson queues();
    };
}
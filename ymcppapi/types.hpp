#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>
#include "nlohmann/adl_serializer.hpp"
#include "nlohmann/detail/abi_macros.hpp"
#include "nlohmann/detail/conversions/to_json.hpp"
#include "nlohmann/detail/macro_scope.hpp"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"



//  Я понятия не имею как написать структуры данных, потом посмотрю у C# обертки, сейчас мозгов не хватает, пока будет просто AsyncJsonResponse возвращать 
using namespace std;
using json = nlohmann::json;

/// Helper namespace for std::variant serialization
namespace utils
{
  namespace details
  {
    template <typename T>
    constexpr auto make_type_name() {
      using namespace std::string_view_literals;
    #ifdef __clang__
      std::string_view name = __PRETTY_FUNCTION__;
      name.remove_prefix("auto utils::details::make_type_name() [T = "sv.size());
      name.remove_suffix("]"sv.size());
    #endif
      return name;
    }
  } // details
  
  /**
  * Convert type T into constexpr string.
  */
  template<typename T>
  constexpr auto type_name_sv = details::make_type_name<T>();
  
  static_assert(type_name_sv<int> == std::string_view{"int"});
} // utils

NLOHMANN_JSON_NAMESPACE_BEGIN
/// https://github.com/nlohmann/json/issues/1749#issuecomment-1731266676
// std::optional serializer
    template<typename T>
    struct adl_serializer<std::optional<T>> {
        static void from_json(const json & j, std::optional<T>& opt) {
            if(j.is_null()) {
                opt = std::nullopt;
            } else {
                opt = j.get<T>();
            }
        }
        static void to_json(json & json, std::optional<T> t) {
            if (t) {
                json = *t;
            } else {
                json = nullptr;
            }
        }
    };

/// https://github.com/nlohmann/json/issues/1261#issuecomment-2048770747
// std::variant serializer
    namespace
    {
    template <typename T, typename... Ts>
    bool variant_from_json(const nlohmann::json& j, std::variant<Ts...>& data) {
    if (j.at("type").get<std::string_view>() != utils::type_name_sv<T>)
        return false;
    data = j.at("data").get<T>();
    return true;
    }
    }

  template <typename... Ts>
  struct adl_serializer<std::variant<Ts...>>
  {
    using Variant = std::variant<Ts...>;
    using Json = nlohmann::json;
    
    static void to_json(Json& j, const Variant& data) {
      std::visit(
        [&j](const auto& v) {
          using T = std::decay_t<decltype(v)>;
          j["type"] = utils::type_name_sv<T>;
          j["data"] = v;
        },
        data);
    }
    
    static void from_json(const Json& j, Variant& data) {
      // Call variant_from_json for all types, only one will succeed
      bool found = (variant_from_json<Ts>(j, data) || ...);
      if (!found)
        throw std::bad_variant_access();
    }
  };
    
NLOHMANN_JSON_NAMESPACE_END

namespace ymapi {
    // Enums:

    enum class Visibility {Private, Public};
    enum class AlbumType {Single, Podcast};
    enum class AlbumMetaType {Single, Podcast, Music};
    enum class CoverType {Pic, Mosaic};

    struct UserSettings {
        int uid;
        bool lastFmScrobblingEnabled;
        bool facebookScrobblingEnabled;
        bool shuffleEnabled;
        bool addNewTrackOnPlaylistTop;
        int volumePercents;
        Visibility userMusicVisibility;
        Visibility userSocialVisibility;
        bool adsDisabled;
        string modified;
        string rbtDisabled;
        string theme;
        bool promosDisabled;
        bool autoPlayRadio;
        bool syncQueueEnabled;
    };

    struct InvocationInfo {
        int exec_duration_millis;
        string hostname;
        string req_id;
        optional<string> app_name;
    };

    struct Error {
        string name;
        string message;
    };

    struct Account {
        string now;
        int uid;
        string login;
        int region;
        string fullName;
        string secondName;
        optional<string> firstName;
        string displayName;
        bool serviceAvailable;
        bool hostedUser;
        vector<string> passport_phones;
    };

    struct Cover{
        bool custom;
        string dir;
        CoverType type;
        optional<vector<string>> itemsUri;
        optional<string> uri;
        optional<string> version;
        optional<string> error;
    };


    struct Track {
        vector<Album> albums;
        vector<Artist> artists;
    };

    struct Artist{
        bool composer;
        optional<bool> decomposed;
        vector<string> genres;
        variant<string, int> id;
        string name;
        bool various;
        optional<vector<Track>> popularTracks;
        optional<bool> ticketsAvailable;
        optional<vector<string>> regions;
    };

    struct Label {
        int id;
        string name;
    };

    struct Album {
        int id;
        optional<string> error;
        string title;
        AlbumType type;
        AlbumMetaType metaType;
        int year;
        string releaseDate;
        string coverUri;
        string ogImage;
        string genre;
        vector<string> buy;
        int trackCount;
        bool recent;
        bool veryImportant;
        vector<Artist> artists;
        vector<vector<Label>> labels;
        bool available;
        bool availableForPremiumUsers;
        bool availableForMobile;
        bool availablePartially;
        vector<int> bests;
        optional<int> prerolls;
        vector<vector<Track>> volumes;
    };


}

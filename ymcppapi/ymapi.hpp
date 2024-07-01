#ifndef YMAPI_H
#define YMAPI_H
#include "cpr/api.h"
#include "cpr/async_wrapper.h"
#include "cpr/body.h"
#include "cpr/parameters.h"
#include "cpr/payload.h"
#include "cpr/session.h"
#include <map>
#include <optional>
#include <variant>
#include "nlohmann/json.hpp"
#endif

#include <string>
#include "cpr/cprtypes.h"

using namespace std;
using json = nlohmann::json;
using AsyncJson = cpr::AsyncWrapper<json>;

namespace ymapi {

  enum class rMethod{GET, POST};

  const string
    OAUTH_URL = "https://oauth.yandex.ru/token",
    API_URL = "https://api.music.yandex.net";

  //"https://api.music.yandex.net"

  const struct _client_data_ 
  {string
          CLIENT_ID = "23cabbbdc6cd418abb4b39c32c41195d",
          CLIENT_SECRET = "53bc75238f0c4d08a118e51fe9203300",
          YM_CLIENT_ID = "YandexMusicAndroid/23020251",
          USER_AGENT = "Yandex-Music-API";

  } client_data;

  cpr::Header 
  construct_headers(
    const string &token,
    const string &language,
    const string &user_agent = client_data.USER_AGENT,
    const string &client_id = client_data.CLIENT_ID
  );

  class 
  YMAPI 
  {
    private:
      cpr::Header headers;
      string token;
      string language;
      shared_ptr<cpr::Session> session = make_shared<cpr::Session>();

    public:
      YMAPI(const string &token, const string &language = "ru");

      optional<AsyncJson> ApiREQ(
        const rMethod,
        const string &url,
        const optional<cpr::Parameters> &query,
        const optional<variant<cpr::Body, cpr::Payload>> &data = nullopt
      );

      optional<AsyncJson> ApiGET(
        const string &endpoint,
        const optional<map<string, string>> &params = nullopt,
        const optional<cpr::Parameters> &query = nullopt
      );

      optional<AsyncJson> ApiPOST(
        const string &endpoint,
        const optional<map<string, string>> &params = nullopt,
        const optional<cpr::Parameters> &query = nullopt,
        const optional<variant<cpr::Body, cpr::Payload>> &data = nullopt
      );

      optional<AsyncJson> oauth(const cpr::Payload &data);
  };
}
#include "ymapi.hpp"
#include "cpr/body.h"
#include "cpr/cprtypes.h"
#include "cpr/payload.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include "fmt/core.h"
#include "fmt/args.h"
#include <variant>


using namespace std;

namespace ymapi {
  string
  fpath(
    const string &url, 
    const map<string, string> &params
    )
  {
    fmt::dynamic_format_arg_store<fmt::format_context> store;
    for (auto const& [key, val]: params) {
      store.push_back(fmt::arg(key.c_str(), val));
    }
    auto result = fmt::vformat(url, store);
    return (result);
  }

  cpr::Header 
  construct_headers(
    const string &token,
    const string &language,
    const string &user_agent,
    const string &client_id
    )
  {
    /**
    @param token User authentication token.
    @param user_agent (Optional) User agent provided in each request
    @param client_id (Optional) Yandex music client id. Set to mobile Android client id by default
    @param language (Optional) "ru" by default. Changes language in retrieved data.
    */
    auto headers = cpr::Header{
      {"X-Yandex-Music-Client", client_id},
      {"User-Agent", user_agent},
      {"Connection", "Keep-Alive"},
      {"Authorization", fmt::format("OAuth {}", token)},
      {"Accept-Language", language}
    };

    return(headers);
  }

  YMAPI::YMAPI(const string &token, const string &language) {
    this->token = token;
    this->language = language;
    this->headers = construct_headers(token, this->language);
  };

  optional<AsyncJson>
  YMAPI::ApiREQ(
    const rMethod method,
    const string &url,
    const optional<cpr::Parameters> &query,
    const optional<variant<cpr::Body, cpr::Payload>> &data)
  { 
    // Default
    this->session->SetUrl(url);
    this->session->SetHeader(this->headers);
    if (query != nullopt) {this->session->SetParameters(query.value());}
    // Data
    if (data != nullopt) {
      if (method == rMethod::GET) {throw invalid_argument("GET request can't send data, use POST instead.");}
      if (const cpr::Body *pval = get_if<cpr::Body>(&data.value())) {
      this->session->SetBody(*pval);
      }
      if (const cpr::Payload *pval = get_if<cpr::Payload>(&data.value())) {
        this->session->SetPayload(*pval);
      }
    }
    // Methods
    if (method == rMethod::GET) {
      AsyncJson future_json = session->GetCallback([](cpr::Response r) {
          return json::parse(r.text);
      });
      return (future_json);
    }
    else {
      AsyncJson future_json = session->PostCallback([](cpr::Response r) {
          return json::parse(r.text);
      });
      return (future_json);
    }
  }

  optional<AsyncJson> 
  YMAPI::ApiGET(
    const string &endpoint,
    const optional<map<string, string>> &params,
    const optional<cpr::Parameters> &query)
  {
    auto url = API_URL + endpoint;
    if (params != nullopt) {url = fpath(url, params.value());}
    return (this->ApiREQ(rMethod::GET, url, query));
  }

  optional<AsyncJson> 
  YMAPI::ApiPOST(
    const string &endpoint,
    const optional<map<string, string>> &params,
    const optional<cpr::Parameters> &query,
    const optional<variant<cpr::Body, cpr::Payload>> &data)
  {
    auto url = API_URL + endpoint;
    if (params != nullopt) {url = fpath(url, params.value());}
    return (this->ApiREQ(rMethod::POST, url, query, data));
  }
}
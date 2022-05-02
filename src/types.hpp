#include <future>
#include <nlohmann/json.hpp>
#include <stdlib.h>
#include <string>
#include <vector>

using string = std::string;
using json = nlohmann::json;
using future_json = std::future<json>;
using future_json_list = std::vector<future_json>;

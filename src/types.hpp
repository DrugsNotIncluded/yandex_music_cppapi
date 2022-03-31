#include <string>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <vector>

using string = std::string;
using json = nlohmann::json;
using future_json = std::future<json>;
using future_json_list = std::vector<future_json>;

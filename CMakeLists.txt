include(FetchContent)
cmake_minimum_required(VERSION 3.12)
project(ymapi)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ymapi STATIC)
file(GLOB YMAPI_SOURCES "src/*.cpp")
target_sources(ymapi PRIVATE "${YMAPI_SOURCES}")
target_include_directories(ymapi PUBLIC src)

#-----------------------------------------------------------------------------
FetchContent_Declare(
  cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG beb9e98806bb84bcc130a2cebfbcbbc6ce62b335
)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_Declare(
  fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9)


FetchContent_MakeAvailable(json fmt cpr)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
if(NOT cpr_POPULATED)
  FetchContent_Populate(cpr)
  set(USE_SYSTEM_CURL ON CACHE BOOL "" FORCE)
  add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR})
endif()

	
target_link_libraries( yandex_music_client PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries( yandex_music_client PRIVATE cpr::cpr)
target_link_libraries( yandex_music_client PRIVATE fmt::fmt)

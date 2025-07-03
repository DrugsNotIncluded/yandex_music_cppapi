include(FetchContent)
cmake_minimum_required(VERSION 3.20)
project(ymcppapi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ymcppapi STATIC
  ymcppapi/ymapi.cpp
  ymcppapi/ymapi.hpp
  ymcppapi/ymclient.cpp
  ymcppapi/ymclient.hpp
)

target_include_directories(ymcppapi PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

execute_process(
  COMMAND git submodule update --init --remote --merge
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git)
FetchContent_Declare(pugixml GIT_REPOSITORY https://github.com/zeux/pugixml.git)
FetchContent_Declare(nlohmann_json GIT_REPOSITORY https://github.com/nlohmann/json.git)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(pugixml)
FetchContent_MakeAvailable(nlohmann_json)
FetchContent_MakeAvailable(fmt)

target_link_libraries(ymcppapi cpr)
target_link_libraries(ymcppapi pugixml)
target_link_libraries(ymcppapi nlohmann_json)
target_link_libraries(ymcppapi fmt)

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  add_custom_target(compile_commands
        WORKING_DIRECTORY ${CMAKE_BUILD_DIR}
        BYPRODUCTS ${CMAKE_SOURCE_DIR}/compile_commands.json
        COMMAND cp -f ./compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
        VERBATIM)
endif()
	

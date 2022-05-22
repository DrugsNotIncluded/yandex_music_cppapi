include(FetchContent)
cmake_minimum_required(VERSION 3.12)
project(ymcppapi)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ymcppapi STATIC
  src/types.hpp
  src/utils.cpp
  src/utils.hpp
  src/ymapi.cpp
  src/ymapi.hpp
)

target_include_directories(ymcppapi PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

execute_process(
  COMMAND git submodule update --init
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory("${PROJECT_SOURCE_DIR}/deps/fmt")
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/cpr")
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/json")

target_link_libraries(ymcppapi PUBLIC nlohmann_json)
target_link_libraries(ymcppapi PUBLIC cpr)
target_link_libraries(ymcppapi PUBLIC fmt)

target_include_directories(ymcppapi PUBLIC $(fmt_INCLUDE_DIRS))
target_include_directories(ymcppapi PUBLIC $(cpr_INCLUDE_DIRS))
target_include_directories(ymcppapi PUBLIC $(nlohmann_json_INCLUDE_DIRS))

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  add_custom_target(compile_commands
        WORKING_DIRECTORY ${CMAKE_BUILD_DIR}
        BYPRODUCTS ${CMAKE_SOURCE_DIR}/compile_commands.json
        COMMAND cp -f ./compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
        VERBATIM)
endif()
	

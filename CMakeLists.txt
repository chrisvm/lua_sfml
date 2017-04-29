cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)
project (lua_sfml)

include_directories(/usr/include/lua5.3)
include_directories(include)

add_executable(lua_sfml src/sfml.cpp)

target_link_libraries(lua_sfml sfml-graphics)
target_link_libraries(lua_sfml sfml-window)
target_link_libraries(lua_sfml sfml-system)
target_link_libraries(lua_sfml lua5.3)

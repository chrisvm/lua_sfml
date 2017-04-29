cmake_minimum_required (VERSION 2.6)
project (lua_sfml)

add_executable(lua_sfml sfml.cpp)
target_link_libraries(lua_sfml sfml-graphics)
target_link_libraries(lua_sfml sfml-window)
target_link_libraries(lua_sfml sfml-system)

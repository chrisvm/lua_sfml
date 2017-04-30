//
// Created by chrisvm on 4/29/17.
//

#ifndef LUA_SFML_ENGINECOMPONENTS_H
#define LUA_SFML_ENGINECOMPONENTS_H
#include <SFML/Graphics.hpp>
#include <sol.hpp>

namespace lua_sfml {
    struct EngineComponents {
        sf::RenderWindow *Window;
        sol::state *SolState;
        EngineComponents();
    };
}

#endif //LUA_SFML_ENGINECOMPONENTS_H

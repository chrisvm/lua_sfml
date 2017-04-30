//
// Created by chrisvm on 4/29/17.
//

#ifndef LUA_SFML_ABSTRACTRENDERABLE_H
#define LUA_SFML_ABSTRACTRENDERABLE_H
#include <SFML/Graphics.hpp>
#include "sol.hpp"

namespace lua_sfml {
    class Renderable {
        static sf::RenderWindow *Window;
    protected:
        Renderable();
    public:
        static sf::RenderWindow* GetGlobalWindow();
        static void SetGlobalWindow(sf::RenderWindow *window);
    };
}

#endif //LUA_SFML_ABSTRACTRENDERABLE_H

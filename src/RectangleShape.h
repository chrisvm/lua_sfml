//
// Created by chrisvm on 4/29/17.
//

#ifndef LUA_SFML_RECTANGLESHAPE_H
#define LUA_SFML_RECTANGLESHAPE_H
#include "Renderable.h"
#include <SFML/Graphics.hpp>
#include "sol.hpp"

namespace lua_sfml {
    class RectangleShape : Renderable {
        sf::RectangleShape _shape;

    public:
        double radius, x, y;

        RectangleShape(double w, double h);
        static void Register(sol::state *state);
        void setFillColor(sf::Color color);
        void draw();
    };
}


#endif //LUA_SFML_RECTANGLESHAPE_H

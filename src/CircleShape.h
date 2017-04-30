//
// Created by chrisvm on 4/29/17.
//

#ifndef LUA_SFML_CIRCLESHAPE_H
#define LUA_SFML_CIRCLESHAPE_H
#include "Renderable.h"
#include <SFML/Graphics.hpp>
#include "sol.hpp"

namespace lua_sfml {
    class CircleShape : Renderable {
        sf::CircleShape _shape;

    public:
        double radius;

        CircleShape(double radius);
        static void Register(sol::state *state);
        void setFillColor(sf::Color color);
        void move(double x, double y);
        double get_x();
        void set_x(double x);
        double get_y();
        void set_y(double y);
        void draw();
    };
}


#endif //LUA_SFML_CIRCLESHAPE_H

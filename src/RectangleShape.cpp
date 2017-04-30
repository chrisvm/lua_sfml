//
// Created by chrisvm on 4/29/17.
//

#include "RectangleShape.h"
using namespace lua_sfml;

lua_sfml::RectangleShape::RectangleShape(double w, double h) {
    sf::Vector2f size(w, h);
    _shape = sf::RectangleShape(size);
}

void lua_sfml::RectangleShape::Register(sol::state *state) {
    state->new_usertype<RectangleShape>("RectangleShape",
                                                        sol::constructors<RectangleShape(double, double)>(),
                                                        "draw", &RectangleShape::draw,
                                                        "setFillColor", &RectangleShape::setFillColor);
}

void lua_sfml::RectangleShape::setFillColor(sf::Color color) {
    _shape.setFillColor(color);
}

void lua_sfml::RectangleShape::draw() {
    Renderable::GetGlobalWindow()->draw(_shape);
}

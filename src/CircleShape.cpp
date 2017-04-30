//
// Created by chrisvm on 4/29/17.
//

#include "CircleShape.h"
using namespace lua_sfml;


CircleShape::CircleShape(double radius)
        : _shape(radius)
{
    this->radius = radius;
}

void CircleShape::draw()
{
    Renderable::GetGlobalWindow()->draw(_shape);
}

void CircleShape::setFillColor(sf::Color color) {
    _shape.setFillColor(color);
}

void CircleShape::Register(sol::state *state) {
    state->new_usertype<lua_sfml::CircleShape>("CircleShape",
                                               sol::constructors<lua_sfml::CircleShape(double)>(),
                                               "radius", &lua_sfml::CircleShape::radius,
                                               "x", sol::property(&CircleShape::get_x, &CircleShape::set_x),
                                               "x", sol::property(&CircleShape::get_y, &CircleShape::set_y),
                                               "draw", &lua_sfml::CircleShape::draw,
                                               "move", &lua_sfml::CircleShape::move,
                                               "setFillColor", &lua_sfml::CircleShape::setFillColor);
}

void CircleShape::move(double x, double y) {
    auto position = _shape.getPosition();
    _shape.setPosition(position.x + x, position.y + y);
}

double CircleShape::get_x() {
    return _shape.getPosition().x;
}

void CircleShape::set_x(double x) {
    _shape.setPosition(x, get_y());
}

double CircleShape::get_y() {
    return _shape.getPosition().y;
}

void CircleShape::set_y(double y) {
    _shape.setPosition(get_x(), y);
}

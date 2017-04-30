//
// Created by chrisvm on 4/29/17.
//
#include "Renderable.h"
using namespace lua_sfml;

sf::RenderWindow* Renderable::Window;

void lua_sfml::Renderable::SetGlobalWindow(sf::RenderWindow *window) {
    Window = window;
}

sf::RenderWindow *lua_sfml::Renderable::GetGlobalWindow() {
    return Window;
}

Renderable::Renderable() {}

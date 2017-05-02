#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include <iostream>
#include <chrono>
#include "EngineComponents.h"
#include "CircleShape.h"

void SetupEngineComponents(lua_sfml::EngineComponents *components);
void CreateWindow(lua_sfml::EngineComponents *components, uint width, uint height);

int main() {
    lua_sfml::EngineComponents components;
    SetupEngineComponents(&components);

	// load update and setup functions
	components.SolState->script_file("script.lua");
	std::function<void(double)> draw_f = (*components.SolState)["draw"];
	std::function<void()> setup_f = (*components.SolState)["setup"];

	// call setup one time
	setup_f();

    // exit if no window created during setup
    if (components.Window == NULL) {
        std::cout << "No window created during setup, exiting." << std::endl;
        return 0;
    }

    // set start of execution
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::ratio<1, 1000>> deltaTime;
	while (components.Window->isOpen()) {
		// pump events
		sf::Event event;
		while (components.Window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				components.Window->close();
				return 0;
			}
		}

        deltaTime = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>
                (std::chrono::steady_clock::now() - endTime);
        endTime = std::chrono::steady_clock::now();
		draw_f(deltaTime.count() * 1.0/1000.0);
	}

	return 0;
}

void SetupEngineComponents(lua_sfml::EngineComponents *components) {
    // load Lua libraries
    components->SolState = new sol::state();
    components->SolState->open_libraries(sol::lib::base, sol::lib::package);

    // create window table
    sol::table windowTable = components->SolState->create_named_table("window");
    windowTable["width"] = 0;
    windowTable["height"] = 0;
    windowTable["antialias"] = 0;
    windowTable["clear"] = [components]() { components->Window->clear(); };
    windowTable["display"] = [components]() { components->Window->display(); };
    windowTable["create"] = [components](uint w, uint h) { CreateWindow(components, w, h); };

    // create colors table
    sol::table colorsTable = components->SolState->create_named_table("color");
    colorsTable["Green"] = sf::Color::Green;
    colorsTable["Red"] = sf::Color::Red;
    colorsTable["Blue"] = sf::Color::Blue;
    colorsTable["White"] = sf::Color::White;
    colorsTable["Black"] = sf::Color::Black;

    // register CircleType
    lua_sfml::CircleShape::Register(components->SolState);
}

void CreateWindow(lua_sfml::EngineComponents *components, uint width, uint height) {
    if (components->Window != NULL) {
        std::cout << "Ignoring call to window.create: window already created." << std::endl;
        return;
    }

    sol::table windowTable = (*components->SolState)["window"];

    sf::ContextSettings settings;
    settings.antialiasingLevel = windowTable["antialias"];
    components->Window = new sf::RenderWindow(sf::VideoMode(width, height), "lua_sfml", sf::Style::Default, settings);
    lua_sfml::Renderable::SetGlobalWindow(components->Window);

    windowTable["width"] = width;
    windowTable["height"] = height;
}

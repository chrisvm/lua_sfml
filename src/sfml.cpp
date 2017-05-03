#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include <iostream>
#include <chrono>
#include "EngineComponents.h"
#include "CircleShape.h"
#include "RectangleShape.h"
#include "Opts.h"

void SetupEngineComponents(lua_sfml::EngineComponents *components);
void CreateWindow(lua_sfml::EngineComponents *components, uint width, uint height);


int main(int argc, char *argv[]) {
    lua_sfml::ArgumentOptions *opts = lua_sfml::ArgumentOptions::GetArgOptions(argc, argv);

    if (opts->ShowHelp) {
        lua_sfml::ArgumentOptions::ShowHelpText();
        return 0;
    }

    if (opts->MainScriptPath == "") {
        std::cout << "No SCRIPT argument given. Try '-h' for help." << std::endl;
        return 0;
    }

    lua_sfml::EngineComponents components;
    SetupEngineComponents(&components);

	// load update and setup functions
	components.SolState->script_file(opts->MainScriptPath);
	std::function<void(double)> update_f = (*components.SolState)["update"];
	std::function<void()> setup_f = (*components.SolState)["setup"];

	// call setup one time
	setup_f();

    // exit if no window created during setup
    if (components.Window == NULL) {
        std::cout << "No window created during setup, exiting." << std::endl;
        return 0;
    }

    // set start of execution time
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::ratio<1, 1000>> deltaTime;

    // game loop
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
		update_f(deltaTime.count() * 1.0/1000.0);
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
    lua_sfml::RectangleShape::Register(components->SolState);
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

#include <SFML/Graphics.hpp>
#include <sol.hpp>

int main() {
	// create window and shape
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// create new Lua state
	sol::state lua;

	// load Lua libraries
    lua.open_libraries(sol::lib::base, sol::lib::package);

	// load update function
	lua.script_file("helloworld.lua");
	std::function<void()> update_f = lua["update"];

	while (window.isOpen()) {
		// pump events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
		}

		// display circle
		window.clear();
		window.draw(shape);
		window.display();

		update_f();
	}

	return 0;
}

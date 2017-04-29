#include <SFML/Graphics.hpp>

int main() {
	// create window and shape
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		// pump events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// display circle
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}

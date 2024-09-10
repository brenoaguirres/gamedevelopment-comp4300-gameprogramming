#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
	// Window and FPS
	const int wWidth = 1280;
	const int wHeight = 720;

	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML Assignment 1");
	window.setFramerateLimit(60);

	// Main Loop
	while (window.isOpen())
	{
		// Event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Rendering
		window.clear();

		window.display();
	}

	return 0;
}
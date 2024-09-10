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

	// Declaring circle
	sf::CircleShape circle(50);
	int r = 0;
	int g = 255;
	int b = 255;
	circle.setFillColor(sf::Color(r, g, b));
	circle.setPosition(300.0f, 300.0f);
	float circleMoveSpeed = 0.01f;

	// Vector
	float rx = 300;
	float ry = 200;
	sf::Vector2f rSize(rx, ry);

	// Declaring rectangle
	sf::RectangleShape re(rSize);
	re.setPosition(100, 5);
	re.setFillColor(sf::Color(255, 255, 0));
	re.setOutlineColor(sf::Color::Red);
	re.setOutlineThickness(20);

	sf::RectangleShape re2(rSize);
	re2.setPosition(400, 200);
	re2.setFillColor(sf::Color::Red);


	// Vector of shapes
	std::vector<sf::CircleShape> circles;
	circles.push_back(circle);
	std::vector<sf::RectangleShape> rectangles;

	// Gradient
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			sf::RectangleShape rect(sf::Vector2f(15, 15));
			rect.setPosition(x * 20, y * 20);
			rect.setFillColor(sf::Color(x * 10, y * 10, 0));
			rectangles.push_back(rect);
		}
	}

	// Font
	sf::Font myFont;

	if (!myFont.loadFromFile("bin/fonts/font.ttf"))
	{
		std::cerr << "Could not load font properly.";
		exit(-1);
	}

	// Text
	sf::Text text("Sample Text", myFont, 24);
	text.setPosition(0, wHeight - (float)text.getCharacterSize());

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

			if (event.key.code == sf::Keyboard::X)
			{
				circleMoveSpeed *= -1.0f;
			}
		}

		// Animation - velocity
		float sx = 0.5f;
		float sy = 0.5f;
		circle.setPosition(circle.getPosition().x + sx, circle.getPosition().y + sy);

		// Rotation
		re.rotate(0.1);
		re2.rotate(0.1);

		// Rendering
		window.clear();
		window.draw(circle);
		window.draw(re);
		window.draw(re2);
		
		// foreach
		for (auto& circ : circles)
		{
			window.draw(circ);
		}

		for (auto& ret : rectangles)
		{
			window.draw(ret);
		}

		window.draw(text);
		window.display();
	}

	return 0;
}
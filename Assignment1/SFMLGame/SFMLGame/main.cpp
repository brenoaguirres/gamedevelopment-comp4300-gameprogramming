#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <fstream>

#define FILEPATH "bin/config.txt"

#pragma region CLASSES
class Shapes
{
	std::shared_ptr<std::vector<sf::CircleShape>> m_circles = std::make_shared<std::vector<sf::CircleShape>>();
	std::shared_ptr<std::vector<sf::RectangleShape>> m_rectangles = std::make_shared<std::vector<sf::RectangleShape>>();
public:
	Shapes(){}
	~Shapes(){}
	void addCircle(sf::CircleShape& circle) const
	{
		m_circles->push_back(circle);
	}

	void addRectangle(sf::RectangleShape& rectangle) const
	{
		m_rectangles->push_back(rectangle);
	}
	void createCircle(sf::CircleShape& circle) const
	{
		addCircle(circle);
	}
	void createRectangle(sf::RectangleShape& rectangle) const
	{
		addRectangle(rectangle);
	}
	void createCircle(float pos_x, float pos_y, float vel_x, float vel_y, int r, int g, int b, float radius) const
	{
		auto circle = std::make_shared<sf::CircleShape>(radius);
		circle->setPosition(pos_x, pos_y);
		circle->setFillColor(sf::Color(r, g, b));

		addCircle(*circle);
	}
	void createRectangle(float pos_x, float pos_y, float vel_x, float vel_y, int r, int g, int b, float width, float height) const
	{
		auto rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
		rectangle->setPosition(pos_x, pos_y);
		rectangle->setFillColor(sf::Color(r, g, b));

		addRectangle(*rectangle);
	}
	const std::vector<sf::CircleShape> getCircleList() const
	{
		return *m_circles;
	}
	const std::vector<sf::RectangleShape> getRectList() const
	{
		return *m_rectangles;
	}
};
#pragma endregion

#pragma region METHODS
void loadFromFile(std::string path)
{
	std::ifstream fin(path);

	while (true) //fix
	{

	}
}
#pragma endregion

#pragma region MAIN
int main(int argc, char* argv[])
{
	// Load Data
	//loadFromFile(FILEPATH);

	std::shared_ptr<Shapes> shapeList = std::make_shared<Shapes>();
	shapeList->createCircle(10, 10, 10, 10, 255, 255, 255, 25);
	shapeList->createCircle(50, 50, 10, 10, 255, 255, 255, 25);
	shapeList->createCircle(100, 100, 10, 10, 255, 255, 255, 25);

	// Window and FPS
	const int wWidth = 1280;
	const int wHeight = 720;

	// Shapes initialization

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
		for (auto shape : shapeList->getCircleList())
		{
			window.draw(shape);
		}
		for (auto shape : shapeList->getRectList())
		{
			window.draw(shape);
		}
		window.display();
	}

	return 0;
}
#pragma endregion
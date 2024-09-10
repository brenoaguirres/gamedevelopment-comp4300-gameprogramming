#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <sstream>
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
	std::vector<sf::CircleShape> getCircleList() const
	{
		return *m_circles;
	}
	std::vector<sf::RectangleShape> getRectList() const
	{
		return *m_rectangles;
	}
};
#pragma endregion

#pragma region METHODS
void loadFromFile(std::string path, int& wWidth, int& wHeight, std::shared_ptr<Shapes> shapes)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "Unable to open file at configured path." << std::endl;
		std::exit(-1);
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream lineStream(line);
		std::string token;
		std::vector<std::string> tokens;

		while (lineStream >> token)
		{
			tokens.push_back(token);
		}

		if (token == "Window")
		{
			wWidth = tokens[1];
			wHeight = tokens[2];
		}
		else if (token == "Font")
		{
			// TODO
		}
		else if (token == "Circle")
		{
			float pos_x, pos_y, vel_x, vel_y, radius;
			int r, g, b;

			fin >> pos_x >> pos_y >> vel_x >> vel_y >> r >> g >> b >> radius;

			shapes->createCircle(pos_x, pos_y, vel_x, vel_y, r, g, b, radius);
		}
		else if (token == "Rectangle")
		{
			float pos_x, pos_y, vel_x, vel_y, width, height;
			int r, g, b;

			fin >> pos_x >> pos_y >> vel_x >> vel_y >> r >> g >> b >> width >> height;

			shapes->createRectangle(pos_x, pos_y, vel_x, vel_y, r, g, b, width, height);
		}
		else {
			std::cout << "Unidentified line token when reading config file." << std::endl;
			std::cout << line << std::endl;
			std::cout << first_key << std::endl;
			continue;
		}
	}

	file.close();
}
#pragma endregion

#pragma region MAIN
int main(int argc, char* argv[])
{
	
	std::shared_ptr<Shapes> shapeList = std::make_shared<Shapes>();
	shapeList->createCircle(10, 10, 10, 10, 255, 255, 255, 25);
	shapeList->createCircle(50, 50, 10, 10, 255, 255, 255, 25);
	shapeList->createCircle(100, 100, 10, 10, 255, 255, 255, 25);

	int wWidth = 1280;
	int wHeight = 720;

	// Load Data
	loadFromFile(FILEPATH, wWidth, wHeight, shapeList);

	// Window initialization
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
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
	std::shared_ptr<std::vector<std::string>> m_labelsCircles = std::make_shared<std::vector<std::string>>();
	std::shared_ptr<std::vector<std::string>> m_labelsRectangles = std::make_shared<std::vector<std::string>>();
	std::shared_ptr<std::vector<sf::Vector2f>> m_velocityCircles = std::make_shared<std::vector<sf::Vector2f>>();
	std::shared_ptr<std::vector<sf::Vector2f>> m_velocityRectangles = std::make_shared<std::vector<sf::Vector2f>>();
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
	void createCircle(std::string label, float pos_x, float pos_y, float vel_x, float vel_y, int r, int g, int b, float radius) const
	{
		// storing circle shape
		auto circle = std::make_shared<sf::CircleShape>(radius);
		circle->setPosition(pos_x, pos_y);
		circle->setFillColor(sf::Color(r, g, b));
		addCircle(*circle);

		// storing circle vel and label
		m_labelsCircles->push_back(label);
		m_velocityCircles->push_back(sf::Vector2f(vel_x, vel_y));
	}
	void createRectangle(std::string label, float pos_x, float pos_y, float vel_x, float vel_y, int r, int g, int b, float width, float height) const
	{
		// storing rect shape
		auto rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
		rectangle->setPosition(pos_x, pos_y);
		rectangle->setFillColor(sf::Color(r, g, b));
		addRectangle(*rectangle);

		// storing rect vel and label
		m_labelsRectangles->push_back(label);
		m_velocityRectangles->push_back(sf::Vector2f(vel_x, vel_y));
	}
	std::vector<sf::CircleShape> getCircleList() const
	{
		return *m_circles;
	}
	std::vector<sf::RectangleShape> getRectList() const
	{
		return *m_rectangles;
	}
	void collision(int scr_w, int scr_h) const
	{
		for (size_t i = 0; i < m_circles->size(); i++)
		{
			auto& circle = (*m_circles)[i];
			auto& velocity = (*m_velocityCircles)[i];
			if (circle.getGlobalBounds().left <= 0 || (circle.getGlobalBounds().left + circle.getLocalBounds().width) >= scr_w)
				velocity.x *= -1;
			if (circle.getGlobalBounds().top <= 0 || (circle.getGlobalBounds().top + circle.getLocalBounds().height) >= scr_h)
				velocity.y *= -1;
				
		}
		for (size_t i = 0; i < m_rectangles->size(); i++)
		{
			auto& rect = (*m_rectangles)[i];
			auto& velocity = (*m_velocityRectangles)[i];
			if (rect.getGlobalBounds().left <= 0 || (rect.getGlobalBounds().left + rect.getLocalBounds().width) >= scr_w)
				velocity.x *= -1;
			if (rect.getGlobalBounds().top <= 0 || (rect.getGlobalBounds().top + rect.getLocalBounds().height) >= scr_h)
				velocity.y *= -1;
		}
	}
	void update() const
	{
		for (size_t i = 0; i < m_circles->size(); ++i)
		{
			auto& circle = (*m_circles)[i];
			auto& velocity = (*m_velocityCircles)[i];
			sf::Vector2f newPosition = circle.getPosition() + velocity;
			circle.setPosition(newPosition);
		}
		for (size_t i = 0; i < m_rectangles->size(); ++i)
		{
			auto& rect = (*m_rectangles)[i];
			auto& velocity = (*m_velocityRectangles)[i];
			sf::Vector2f newPosition = rect.getPosition() + velocity;
			rect.setPosition(newPosition);
		}
	}
};
#pragma endregion

#pragma region METHODS
bool loadConfig(std::string path, int& wWidth, int& wHeight, std::shared_ptr<Shapes> shapes)
{
	std::ifstream file(path);
	
	if (!file.is_open())
	{
		std::cerr << "File not found at " + path + " specified path." << std::endl;
		return false;
	}

	std::string param;

	while (!file.eof())
	{
		file >> param;
		if (param == "Window")
		{
			int w, h;
			file >> w >> h;
			wWidth = w;
			wHeight = h;
			
			std::cout << "Window loaded" << std::endl;
		}
		else if (param == "Font")
		{
			std::string path;
			int size, r, g, b;
			file >> path >> size >> r >> g >> b;
			std::cout << "Font loaded" << std::endl;
		}
		else if (param == "Circle")
		{
			std::string label;
			float px, py, vx, vy, radius;
			int r, g, b;
			file >> label >> px >> py >> vx >> vy >> r >> g >> b >> radius;
			shapes->createCircle(label, px, py, vx, vy, r, g, b, radius);
			std::cout << "Circle loaded" << std::endl;
		}
		else if (param == "Rectangle")
		{
			std::string label;
			float px, py, vx, vy, width, height;
			int r, g, b;
			file >> label >> px >> py >> vx >> vy >> r >> g >> b >> width >> height;
			shapes->createRectangle(label, px, py, vx, vy, r, g, b, width, height);
			std::cout << "Rectangle loaded" << std::endl;
		}
		else
		{
			std::cout << "Unidentified token within config file: "  ". Could not load properly." << std::endl;
		}
	}

	file.close();
	return true;
}
#pragma endregion

#pragma region MAIN
int main(int argc, char* argv[])
{
	
	std::shared_ptr<Shapes> shapeList = std::make_shared<Shapes>();

	int wWidth = 1280;
	int wHeight = 720;

	// Load Data
	if (!loadConfig(FILEPATH, wWidth, wHeight, shapeList))
		return -1;

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

		// Collision
		shapeList->collision(wWidth, wHeight);
		// Update
		shapeList->update();

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
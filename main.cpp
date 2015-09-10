#include "Application.h"

int main(){
	Application app;
	app.run();
	return 0;
}

//SFML TEST

//#include <SFML/Graphics.hpp>
//int main(){
//sf::ContextSettings settings;
//settings.antialiasingLevel = 1;
//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default, settings);
//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//sf::CircleShape shape(100.f);
//shape.setFillColor(sf::Color::Green);

//while (window.isOpen())
//{
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			window.close();
//	}

//	window.clear();
//	window.draw(shape);
//	window.display();
//}
//return 0;
//}
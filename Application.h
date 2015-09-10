#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Context.h"

class Application{
private:
	void processEvents();
	//void processDebugInput();
	void update(const sf::Time& dt);
	//void updateDebug(const sf::Time& dt);
	void renderDebug();
	void render();

	//sf::CircleShape circle_;
	//bool debug_;

public:
	Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);
	Application();
	~Application();
	void run();
};


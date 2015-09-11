#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Context.h"
#include "States/TitleState.h"

class Application{
private:
	void processEvents();
	void update(const sf::Time& dt);
	void render();

public:
	Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);
	Application();
	~Application();
	void run();
};


#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <iomanip>

class State;

class Application{
public:
	Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);
	Application();
	~Application();
	void run();

	sf::RenderWindow& getWindow();
	void changeState(State* state);
	std::ostringstream& getConsole();
	std::ostringstream& operator<<(const std::string& info);
private:
	void processEvents();
	void update(const sf::Time& dt);
	void render();

	sf::RenderWindow window_;
	bool hasFocus_;
	std::unique_ptr<State> state_;

	struct Console{
		Console();
		void update(const sf::Time& dt);

		bool up_;
		sf::Time timeSinceFpsUpdate_;
		const sf::Time TimePerFpsUpdate_;
		unsigned int frameCounter_;
		unsigned int updateCounter_;
		float currentFps_;
		float currentUps_;
		sf::Font font_;
		std::ostringstream stream_;
		sf::Text text_;
	} console_;
};


#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class Context{
public:
	static Context& instance();
	sf::RenderWindow window_;

	//void processEvent(const sf::Event& ev);
	void update(const sf::Time& dt);
	void renderState();
	void changeDebug();

private:
	void renderDebug();

	Context();
	Context(const Context&) = delete;
	Context& operator=(const Context&) = delete;

	//std::vector<std::unique_ptr<State*>> states_;
	bool debug_;
	sf::Time timePassed_;
	const sf::Time TimePerFpsUpdate_;
	unsigned int frameCounter_;
	unsigned int updateCounter_;
	float fps_;
	float ups_;
};


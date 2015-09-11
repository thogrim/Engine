#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "States/State.h"

class Context{
	friend class Application;
public:
	static Context& instance();
	sf::RenderWindow window_;

	void pushState(State* state);
	void popState();
	void changeState(State* state);

	bool isValid() const;
	void changeDebug();

	//void forwardKeyPressed
	void update(const sf::Time& dt);
	void render();
private:
	Context();
	Context(const Context&) = delete;
	Context& operator=(const Context&) = delete;
	void renderDebug();

	std::vector<std::unique_ptr<State>> states_;

	//debug info
	bool debug_;
	sf::Time timePassed_;
	const sf::Time TimePerFpsUpdate_;
	unsigned int frameCounter_;
	unsigned int updateCounter_;
	float fps_;
	float ups_;
	sf::Font debugFont_;
	sf::Text debugInfo_;
};


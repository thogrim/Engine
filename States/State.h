#pragma once

#include <SFML/Graphics.hpp>
//#include "../Context.h"

class State{
public:
	State();
	~State();

private:
	virtual void loadTextures() = 0;
	virtual void loadFonts() = 0;
	virtual void loadSound() = 0;

public:
	void init();
	//void processKeyPressed()=0;
	//void processAnotherEventType()=0;
	virtual void update(const sf::Time& dt) = 0;
	virtual void render() const = 0;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


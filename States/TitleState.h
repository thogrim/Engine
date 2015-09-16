#pragma once

#include "State.h"
#include "../Context.h"
#include "../World.h"

class TitleState: public State{
public:
	TitleState();
	~TitleState();

private:
	void loadTextures();
	void loadFonts();
	void loadSound();

public:
	void processKeyPressed(sf::Keyboard::Key key);
	void update(const sf::Time& dt);
	void render() const;
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	//ResourceHolders
	World world_;
};


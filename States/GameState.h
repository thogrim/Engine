#pragma once

#include "State.h"
#include "TitleState.h"
#include "../World.h"
#include "../Actions/MoveBy.h"

class GameState: public State{
public:
	GameState();
	~GameState();

private:
	void loadTextures();
	void loadFonts();
	void loadSound();

public:
	void processKeyPressed(sf::Keyboard::Key key);
	void processResized(const sf::Event::SizeEvent& size);
	void update(const sf::Time& dt);
	void render() const;
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	//ResourceHolders
	World world_;
	Actions::Action* action_;
};


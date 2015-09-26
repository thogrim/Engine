#pragma once

#include "State.h"
#include "../World.h"

namespace Actions{
	class Action;
}

class GameState: public State{
public:
	GameState(Application& app);
	~GameState();

private:
	void loadTextures();
	void loadFonts();
	void loadSound();

public:
	void processKeyPressed(sf::Keyboard::Key key);
	void processResized(const sf::Event::SizeEvent& size);
	void update(const sf::Time& dt);
	//void render() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	//ResourceHolders
	World world_;
	Actions::Action* action_;
};


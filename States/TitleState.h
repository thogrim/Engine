#pragma once

#include "State.h"
#include "../World.h"
#include "../ActionContainer.h"

class TitleState: public State{
public:
	TitleState(Application& app);
	TitleState(const State& state);
	~TitleState();

public:
	void withActionUpdate(const sf::Time& dt);
	void noActionUpdate(const sf::Time& dt);
	void onKeyPressed(sf::Keyboard::Key key);
	void onResized(const sf::Event::SizeEvent& size);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	World world_;
	sf::RectangleShape shape_;
	ActionContainer ac_;
	ActionContainer ac2_;
	ActionContainer ac3_;
};


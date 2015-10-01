#pragma once

#include "State.h"
#include "../World.h"
#include "../ActionContainer.h"
//test
#include "../GUI/Component.h"

class TitleState: public State{
public:
	TitleState(Application& app);
	TitleState(const State& state);
	~TitleState();

protected:
	void init();
	void withActionUpdate(const sf::Time& dt);
	void noActionUpdate(const sf::Time& dt);
	void onKeyPressed(sf::Keyboard::Key key);
	void onResized(const sf::Event::SizeEvent& size);
	void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton);
	void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton);
	void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	World world_;
	sf::RectangleShape shape_;
	ActionContainer ac_;
	ActionContainer ac2_;
	ActionContainer ac3_;

	//test
	GUI::Component testButton_;
};


#pragma once

#include <SFML/Graphics.hpp>

class StateBehaviour: public sf::Drawable{
public:
	StateBehaviour() = default;
	virtual ~StateBehaviour() = default;
	virtual void onKeyPressed(sf::Keyboard::Key key) = 0;
	virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton) = 0;
	virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton) = 0;
	virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove) = 0;
	virtual void update(const sf::Time& dt) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


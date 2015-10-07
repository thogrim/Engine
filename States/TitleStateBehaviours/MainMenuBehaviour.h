#pragma once

#include "../StateBehaviour.h"

namespace GUI{
	class Menu;
}

class MainMenuBehaviour: public StateBehaviour{
public:
	MainMenuBehaviour(GUI::Menu& mainMenu);
	~MainMenuBehaviour();
	void onKeyPressed(sf::Keyboard::Key key);
	void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton);
	void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton);
	void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove);
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	GUI::Menu& mainMenu_;
};


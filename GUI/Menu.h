#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace GUI{

	class Component;

	class Menu: public sf::Transformable, public sf::Drawable{
	public:
		Menu();
		~Menu();
		void addComponent(Component* c);
		void setTexture(const sf::Texture& texture);
		void setText(const std::string& string, const sf::Font& font, unsigned int characterSize);
		void setTextPosition(float x, float y);
		void setActive(bool active);
		void onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton);
		void onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton);
		void onMouseMoved(sf::Event::MouseMoveEvent mouseMove);
		void update(const sf::Time& dt);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Sprite sprite_;
		sf::Text text_;
		std::vector<Component*> components_;
		Component* hoveredComponent_;
		Component* pressedComponent_;
		bool active_;
	};
}
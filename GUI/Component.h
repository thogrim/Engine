#pragma once

#include <SFML/Graphics.hpp>
#include "../ActionContainer.h"

class GuiObserver;

namespace GUI{
	class Component: public ActionContainer, public sf::Transformable, public sf::Drawable{
		friend class Menu;
	public:
		Component();
		virtual ~Component();
		virtual void setTexture(const sf::Texture& texture);
		void setText(const std::string& string, const sf::Font& font, unsigned int characterSize);
		void setTextPosition(float x, float y);
		void setObserver(GuiObserver* obs);
		void setActive(bool active);
		//void setColor(sf::Color color);
		//sf::Sprite& getSprite();
		//const sf::FloatRect& getSize() const;
		bool contains(float x, float y) const;
		//virtual ?
		void onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton);
		void onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton);
		void onMouseMoved(sf::Event::MouseMoveEvent mouseMove);
		//TODO:
		virtual void onMouseEnter()=0;
		virtual void onMouseLeave()=0;
		virtual void onSpritePressed()=0;
		virtual void onSpriteReleased() = 0;

		virtual void update(const sf::Time& dt);//update animacji?
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	protected:
		sf::Sprite sprite_;//or Animation? or maybe sprite and animation
		sf::Text text_;
		bool hovered_;
		bool pressed_;
		bool active_;
	private:
		GuiObserver* observer_;
	};
}
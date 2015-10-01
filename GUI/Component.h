#pragma once

#include <SFML/Graphics.hpp>
#include "../ActionContainer.h"

class GuiObserver;

namespace GUI{
	class Component: public ActionContainer, public sf::Transformable, public sf::Drawable{
	public:
		Component();
		virtual ~Component();
		void setObserver(GuiObserver* obs);
		void setTexture(const sf::Texture& texture);
		void setParent(Component* parent);//should this be protected?
		//virtual ?
		virtual void onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton);
		virtual void onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton);
		virtual void onMouseMoved(sf::Event::MouseMoveEvent mouseMove);
		//TODO:
		//functions affecting sprite
		//virtual void onMouseEnter()=0;
		//virtual void onMouseLeave()=0;
		//virtual void onPressed()=0;
		//virtual void onReleased() = 0;
		virtual void update(const sf::Time& dt);//update animacji?
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	protected:
		//void notifyObserver();

		sf::Sprite sprite_;//or Animation? or maybe sprite and animation
		bool hovered_;
		bool pressed_;
		Component* parent_;

	private:
		GuiObserver* observer_;
	};
}
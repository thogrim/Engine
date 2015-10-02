#pragma once

//#include <iostream>
#include "Component.h"

namespace GUI{
	class Button : public Component{
	public:
		Button();
		~Button();
		void setTexture(const sf::Texture& texture);
		void onMouseEnter();
		void onMouseLeave();
		void onSpritePressed();
		void onSpriteReleased();
	private:
		sf::IntRect normalRect_;
		sf::IntRect hoveredRect_;
		sf::IntRect pressedRect_;
	};
}
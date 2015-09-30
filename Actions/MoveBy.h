#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "SimpleAction.h"

namespace Actions{
	class MoveBy: public SimpleAction{
	public:
		MoveBy(/*ActionObserver* obs, */const sf::Time& duration, sf::Transformable& object, float dx, float dy);
		~MoveBy();
	private:
		void updateAction(const sf::Time& dt);
		sf::Transformable& object_;
		sf::Vector2f velocity_;
	};
}
#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "SimpleAction.h"

namespace Actions{
	class Rotate : public SimpleAction{
	public:
		Rotate(ActionObserver* obs, const sf::Time& duration, sf::Transformable& object, float angle);
		~Rotate();
	private:
		void updateAction(const sf::Time& dt);
		sf::Transformable& object_;
		float velocity_;
	};
}
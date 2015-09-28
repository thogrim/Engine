#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "Action.h"

namespace Actions{
	class MoveBy: public Action{
	public:
		MoveBy(ActionObserver& obs, const sf::Time& duration, sf::Transformable& object, float dx, float dy);
		~MoveBy();
		Action* clone() const;
	private:
		void updateAction(const sf::Time& dt);
		sf::Transformable& object_;
		sf::Vector2f velocity_;
	};
}
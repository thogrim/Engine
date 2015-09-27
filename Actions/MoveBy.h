#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "SimpleAction.h"

namespace Action{
	class MoveBy: public SimpleAction{
	public:
		MoveBy(ActionObserver& obs, const sf::Time& duration, sf::Transformable& object, float dx, float dy);
		~MoveBy();
		void update(const sf::Time& dt);
		SimpleAction* clone() const;
	private:
		sf::Transformable& object_;
		sf::Vector2f velocity_;
	};
}
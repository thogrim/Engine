#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include "Action.h"

namespace Actions{
	class MoveBy: public Action{
	public:
		MoveBy(sf::View& camera, float dx, float dy, float time);
		~MoveBy();
		void update(const sf::Time& dt);
	private:
		sf::View& camera_;
		sf::Vector2f velocity_;
		sf::Time timeLeft_;
	};
}
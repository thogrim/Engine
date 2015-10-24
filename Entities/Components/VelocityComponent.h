#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

struct VelocityComponent{
	VelocityComponent(const sf::Vector2f& velocity, sf::Transformable& transform)
		:velocity_(velocity),
		transform_(transform){
	}
	sf::Vector2f velocity_;
	sf::Transformable& transform_;
};


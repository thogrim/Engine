#pragma once

#include <SFML/Graphics/Transformable.hpp>

struct RotateComponent{
	RotateComponent(float velocity, sf::Transformable& transform)
		:velocity_(velocity),
		transform_(transform){
	}
	float velocity_;
	sf::Transformable& transform_;
};
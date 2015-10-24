#pragma once

#include <SFML/Graphics/Transformable.hpp>

struct TransformComponent{
	TransformComponent(const sf::Transformable& transform)
		:transform_(transform){
	}
	sf::Transformable transform_;
};
#pragma once

#include <SFML/Graphics/Sprite.hpp>

struct SpriteComponent{
	SpriteComponent(const sf::Texture& tex, sf::Transformable& transform)
		:sprite_(),
		transform_(transform){
		sprite_.setTexture(tex);
	}
	sf::Sprite sprite_;
	sf::Transformable& transform_;
};
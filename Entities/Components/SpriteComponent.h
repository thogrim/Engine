#pragma once

#include <SFML/Graphics/Sprite.hpp>
//for test!
#include <iostream>

struct SpriteComponent{
	SpriteComponent(const sf::Texture& tex, sf::Transformable& transform)
		:sprite_(),
		transform_(transform){
		sprite_.setTexture(tex);
	}
	~SpriteComponent(){
		std::cout << "d-tor from sprite comp called!\n";
	}
	sf::Sprite sprite_;
	sf::Transformable& transform_;
};
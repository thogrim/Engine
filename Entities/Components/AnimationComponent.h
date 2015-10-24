#pragma once

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>

struct AnimationComponent{
	AnimationComponent(const std::vector<sf::Time, sf::IntRect>& frames)
		:frames_(frames),
		currentFrame_(0),
		frameDuration_(sf::Time::Zero){
	}
	std::vector<sf::Time, sf::IntRect> frames_;
	unsigned int currentFrame_;
	sf::Time frameDuration_;
};
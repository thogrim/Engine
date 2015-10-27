#pragma once

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

struct AnimationComponent{
	AnimationComponent(const sf::Vector2i& frameSize, unsigned int nFrames, const sf::Time& frameDuration)
		:frameSize_(frameSize),
		nFrames_(nFrames),
		currentFrame_(0),
		frameDuration_(frameDuration){
	}
	const sf::Vector2i frameSize_;
	const unsigned int nFrames_;
	unsigned int currentFrame_;
	const sf::Time frameDuration_;
	sf::Time timePassed_;
};
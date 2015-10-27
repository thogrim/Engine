#pragma once

#include "BaseSystem.h"
#include "../Components/AnimationComponent.h"

class SpriteSystem;

class AnimationSystem: public BaseSystem<AnimationComponent>{
public:
	AnimationSystem(SpriteSystem& spriteSystem);
	~AnimationSystem() = default;
	void update(const sf::Time& dt);
private:
	SpriteSystem& spriteSystem_;
};
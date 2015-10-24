#pragma once

#include "BaseSystem.h"
#include "../Components/SpriteComponent.h"

class SpriteSystem : public BaseSystem<SpriteComponent>, public sf::Drawable{
public:
	SpriteSystem();
	~SpriteSystem() = default;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
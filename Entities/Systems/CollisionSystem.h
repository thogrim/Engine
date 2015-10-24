#pragma once

#include "BaseSystem.h"
#include "../Components/CollisionComponent.h"

class CollisionSystem : public BaseSystem<CollisionComponent>, public sf::Drawable{
public:
	CollisionSystem();
	~CollisionSystem() = default;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
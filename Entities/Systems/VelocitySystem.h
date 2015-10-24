#pragma once

#include <SFML/System/Time.hpp>
#include "BaseSystem.h"
#include "../Components/VelocityComponent.h"

class VelocitySystem : public BaseSystem<VelocityComponent>{
public:
	VelocitySystem();
	~VelocitySystem() = default;
	void update(const sf::Time& dt);
};
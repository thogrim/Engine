#pragma once

#include <SFML/System/Time.hpp>
#include "BaseSystem.h"
#include "../Components/RotateComponent.h"

class RotateSystem: public BaseSystem<RotateComponent>{
public:
	RotateSystem();
	~RotateSystem() = default;
	void update(const sf::Time& dt);
};
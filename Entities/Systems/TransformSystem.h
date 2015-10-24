#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "BaseSystem.h"
//#include "../Components/TransformComponent.h"

typedef BaseSystem<sf::Transformable> TransformSystem;

//class TransformSystem: public BaseSystem<sf::Transformable>{
//public:
//	TransformSystem();
//	~TransformSystem() = default;
//};
#pragma once

#include "BaseSystem.h"
#include "../Components/AIComponent.h"
#include "../EntityBehaviourObserver.h"

class EntitySystem;

class AISystem: public BaseSystem<AIComponent>, public EntityBehaviourObserver{
public:
	AISystem(EntitySystem& entitySystem);
	//void addComponent(unsigned int ID, AIComponent& component) override;
	void update(const sf::Time& dt);
	void onEntityEvent();
private:
	EntitySystem& entitySystem_;
	unsigned int processedComp_;
};
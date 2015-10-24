#include "VelocitySystem.h"

VelocitySystem::VelocitySystem()
	:BaseSystem(){
}

void VelocitySystem::update(const sf::Time& dt){
	for (auto& comp : components_){
		comp.second.transform_.move(comp.second.velocity_*dt.asSeconds());
	}
}
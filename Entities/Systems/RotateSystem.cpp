#include "RotateSystem.h"

RotateSystem::RotateSystem()
	:BaseSystem(){
}

void RotateSystem::update(const sf::Time& dt){
	for (auto& comp : components_){
		comp.second.transform_.rotate(comp.second.velocity_*dt.asSeconds());
	}
}
#include "CollisionSystem.h"
#include <SFML/Graphics/RenderTarget.hpp>

CollisionSystem::CollisionSystem()
	:BaseSystem(){
}

void CollisionSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto& comp : components_){
		states.transform = comp.second.transform_.getTransform();
		target.draw(*comp.second.shape_, states);
	}
}
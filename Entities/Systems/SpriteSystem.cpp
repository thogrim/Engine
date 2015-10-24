#include "SpriteSystem.h"
#include <SFML/Graphics/RenderTarget.hpp>

SpriteSystem::SpriteSystem()
	:BaseSystem(){
}

void SpriteSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto& comp : components_){
		states.transform = comp.second.transform_.getTransform();
		target.draw(comp.second.sprite_, states);
	}
}
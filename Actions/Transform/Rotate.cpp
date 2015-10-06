#include "Rotate.h"

using namespace Actions;

Rotate::Rotate(const sf::Time& duration, sf::Transformable& object, float angle)
	:SimpleAction(duration),
	object_(object),
	velocity_(angle/duration.asSeconds()){
}

Rotate::~Rotate(){
}

void Rotate::updateAction(const sf::Time& dt){
	object_.rotate(velocity_*dt.asSeconds());
}
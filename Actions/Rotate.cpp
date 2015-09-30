#include "Rotate.h"

using namespace Actions;

Rotate::Rotate(/*ActionObserver* obs,*/ const sf::Time& duration, sf::Transformable& object, float angle)
	:SimpleAction(/*obs,*/ duration),
	object_(object),
	velocity_(angle/duration.asSeconds()){
}

Rotate::~Rotate(){
}

void Rotate::updateAction(const sf::Time& dt){
	object_.rotate(velocity_*dt.asSeconds());
}
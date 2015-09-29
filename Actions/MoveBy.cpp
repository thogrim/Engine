#include "MoveBy.h"

using namespace Actions;

MoveBy::MoveBy(ActionObserver* obs, const sf::Time& duration, sf::Transformable& object, float dx, float dy)
	:SimpleAction(obs,duration),
	object_(object),
	velocity_(dx/duration.asSeconds(),dy/duration.asSeconds()){
}

MoveBy::~MoveBy(){
}

void MoveBy::updateAction(const sf::Time& dt){
	object_.move(velocity_*dt.asSeconds());
}
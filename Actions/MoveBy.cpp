#include "MoveBy.h"

using namespace Action;

MoveBy::MoveBy(ActionObserver& obs, const sf::Time& duration, sf::Transformable& object, float dx, float dy)
	:SimpleAction(obs,duration),
	object_(object),
	velocity_(dx/duration.asSeconds(),dy/duration.asSeconds()){
}

MoveBy::~MoveBy(){
}

void MoveBy::update(const sf::Time& dt){
	object_.move(velocity_*dt.asSeconds());

	timeLeft_ -= dt;
	if (timeLeft_ < sf::Time::Zero)
		notifyCompletion();
}

SimpleAction* MoveBy::clone() const{
	return new MoveBy(*this);
}

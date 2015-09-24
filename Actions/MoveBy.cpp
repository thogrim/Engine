#include "MoveBy.h"

using namespace Actions;

MoveBy::MoveBy(sf::View& camera, float dx, float dy, float time)
	:Action(),
	camera_(camera),
	velocity_(dx/time,dy/time),
	timeLeft_(sf::seconds(time)){
}

MoveBy::~MoveBy(){
}

void MoveBy::update(const sf::Time& dt){
	if (!done_){
		camera_.move(velocity_*dt.asSeconds());
		timeLeft_ -= dt;
		if (timeLeft_ < sf::Time::Zero)
			done_ = true;
	}
}


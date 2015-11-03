#include "Wait.h"

Wait::Wait(const EntityEvent& ev, const sf::Time& duration)
	:EntityBehaviour(ev),
	timeLeft_(duration),
	duration_(duration){
}

//Wait::~Wait(){
//
//}

void Wait::update(const sf::Time& dt){
	//if duration time passed
	if (timeLeft_ < sf::Time::Zero){
		//reset timer
		timeLeft_ = duration_;
		//notify observer
		notifyObserver();
	}
	//else wait
	else
		timeLeft_ -= dt;
}
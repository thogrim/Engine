#include "SimpleAction.h"
#include "../ActionObserver.h"

using namespace Actions;

SimpleAction::SimpleAction(const sf::Time& duration)
	:Action(),
	initialTime_(duration),
	timeLeft_(duration){
}

SimpleAction::~SimpleAction(){
}

void SimpleAction::update(const sf::Time& dt){
	//check whether action is done
	//and notify observer if it is
	if (timeLeft_ <= sf::Time::Zero){
		timeLeft_ = initialTime_;
		assert(observer_);
		observer_->onActionFinish();
	}

	//else update action
	else{
		if (dt > timeLeft_){
			updateAction(timeLeft_);
			timeLeft_ -= timeLeft_;//this looks weird, but it works and timeLeft_ = sf::Time::Zero for some reason does not
		}
		else{
			updateAction(dt);
			timeLeft_ -= dt;
		}
	}
}
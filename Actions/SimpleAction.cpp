#include "SimpleAction.h"
#include "../ActionObserver.h"

using namespace Actions;

SimpleAction::SimpleAction(/*ActionObserver* obs ,*/ const sf::Time& duration)
	:Action(/*obs*/),
	initialTime_(duration),
	timeLeft_(duration){
}

SimpleAction::~SimpleAction(){
}

void SimpleAction::update(const sf::Time& dt){
	//check whether action is done
	//and notify observer if it is
	if (timeLeft_ < sf::Time::Zero){
		timeLeft_ = initialTime_;
		assert(observer_);
		observer_->onActionFinish();
	}

	//else update action
	else{
		updateAction(dt);
		timeLeft_ -= dt;
	}
}
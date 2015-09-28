#include "Action.h"
#include "../ActionObserver.h"

//using namespace Action;

Action::Action(ActionObserver& obs, const sf::Time& duration)
	:observer_(obs),
	timeLeft_(duration){
}

Action::~Action(){
}

void Action::update(const sf::Time& dt){
	//update action
	updateAction(dt);

	//check whether action is done
	//and notify observer if it is
	timeLeft_ -= dt;
	if (timeLeft_ < sf::Time::Zero)
		observer_.onActionFinish();
}

//void Action::reset(){
//	timeLeft_ = sf::seconds(2.f);
//}

//void Action::notifyCompletion(){
//	observer_.onActionFinish();
//}
#include "SimpleAction.h"
#include "../ActionObserver.h"

using namespace Action;

SimpleAction::SimpleAction(ActionObserver& obs, const sf::Time& duration)
	:observer_(obs),
	timeLeft_(duration){
}

SimpleAction::~SimpleAction(){
}

void SimpleAction::reset(){
	timeLeft_ = sf::seconds(2.f);
}

void SimpleAction::notifyCompletion(){
	observer_.onActionFinish();
}
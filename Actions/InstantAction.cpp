#include "InstantAction.h"
#include "../ActionObserver.h"

using namespace Actions;

InstantAction::InstantAction()
	:Action(){
}

InstantAction::~InstantAction(){
}

void InstantAction::update(const sf::Time& dt){
	//perform action and notify observer
	//right after
	updateAction(dt);
	assert(observer_);
	observer_->onActionFinish();
}
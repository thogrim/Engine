#include "ActionContainer.h"
#include "Actions/Action.h"

ActionContainer::ActionContainer()
	:action_(nullptr){
}

ActionContainer::~ActionContainer(){
	assert(action_);
	delete action_;
}

void ActionContainer::storeAction(Action* action){
	action_ = action;
}

Action* ActionContainer::getAction() const{
	assert(action_);
	return action_;
}
#include "ActionContainer.h"
#include "Actions/Action.h"

ActionContainer::ActionContainer()
	:action_(nullptr){
}

ActionContainer::~ActionContainer(){
	if (action_)
		delete action_;
}

void ActionContainer::storeAction(Action* action){
	action_ = action;
}

Action* ActionContainer::getAction() const{
	return action_;
}
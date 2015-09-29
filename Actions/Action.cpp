#include "Action.h"

Action::Action(ActionObserver* obs)
	:observer_(obs){
}

Action::~Action(){
}

void Action::setObserver(ActionObserver* obs){
	observer_ = obs;
}
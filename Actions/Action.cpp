#include "Action.h"

Action::Action()
	:observer_(nullptr){
}

Action::~Action(){
}

void Action::setObserver(ActionObserver* obs){
	observer_ = obs;
}
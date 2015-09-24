#include "Action.h"

using namespace Actions;

Action::Action()
	:done_(false){
}

Action::~Action(){
}

bool Action::done() const{
	return done_;
}

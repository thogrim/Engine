#include "ActionQueue.h"

using namespace Actions;

ActionQueue::ActionQueue()
	:Action(),
	actions_(),
	currentAction_(0){
}

ActionQueue::~ActionQueue(){
	for (Action* a : actions_){
		delete a;
	}
}

void ActionQueue::addAction(Action* a){
	a->setObserver(this);
	actions_.push_back(a);
}

void ActionQueue::update(const sf::Time& dt){
	//notify if all actions are done
	if (currentAction_ == actions_.size()){
		currentAction_ = 0;
		assert(observer_);
		observer_->onActionFinish();
	}

	else
		updateAction(dt);
}

void ActionQueue::onActionFinish(){
	++currentAction_;
}

void ActionQueue::updateAction(const sf::Time& dt){
	actions_[currentAction_]->update(dt);
}
#include "CompositeAction.h"

using namespace Actions;

CompositeAction::CompositeAction(/*ActionObserver* obs*/)
	:Action(/*obs*/),
	actions_(),
	currentAction_(0),
	finishedActions_(0){
}

CompositeAction::~CompositeAction(){
	for (const auto& a : actions_){
		delete a.first;
	}
}

void CompositeAction::addAction(Action* a){
	a->setObserver(this);
	actions_.emplace_back(a, true);
}

void CompositeAction::update(const sf::Time& dt){
	//notify if all actions are finished
	if (finishedActions_ == actions_.size()){
		for (auto& a : actions_){
			a.second = true;
		}
		finishedActions_ = 0;
		assert(observer_);
		observer_->onActionFinish();
	}
	//else update action
	else
		updateAction(dt);
}

void CompositeAction::onActionFinish(){
	actions_[currentAction_].second = false;
	++finishedActions_;
}

void CompositeAction::updateAction(const sf::Time& dt){
	currentAction_ = 0;
	for (auto it = actions_.begin(); it != actions_.end(); ++it){
		if (it->second)
			it->first->update(dt);
		++currentAction_;
	}
}
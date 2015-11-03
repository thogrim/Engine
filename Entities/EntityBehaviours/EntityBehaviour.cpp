#include "EntityBehaviour.h"
#include "../EntityBehaviourObserver.h"

EntityBehaviour::EntityBehaviour(const EntityEvent& ev)
	:event_(ev),
	observer_(nullptr){
}

EntityBehaviour::~EntityBehaviour(){
}

void EntityBehaviour::setObserver(EntityBehaviourObserver* observer){
	observer_ = observer;
}

void EntityBehaviour::notifyObserver(){
	observer_->onEntityEvent();
}

const EntityEvent& EntityBehaviour::getEvent() const{
	return event_;
}
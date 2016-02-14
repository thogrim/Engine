#include "EntityBehaviour.h"
#include "../EntityBehaviourObserver.h"

//EntityBehaviour::EntityBehaviour(const std::vector<EntityEvent>& events)
//	:events_(events),
//	observer_(nullptr){
//}

EntityBehaviour::EntityBehaviour(const std::vector<EntityEvent>& events)
	:events_(events),
	observer_(nullptr){
}

EntityBehaviour::EntityBehaviour(const EntityEvent& ev)
	:events_(),
	observer_(nullptr){
	events_.reserve(1);
	events_.push_back(ev);
}

EntityBehaviour::~EntityBehaviour(){
}

void EntityBehaviour::setObserver(EntityBehaviourObserver* observer){
	observer_ = observer;
}

void EntityBehaviour::notifyObserver(){
	observer_->onEntityEvent();
}

std::vector<EntityEvent>& EntityBehaviour::getEvents(){
	return events_;
}
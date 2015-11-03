#include "AISystem.h"
#include "../EntitySystem.h"

AISystem::AISystem(EntitySystem& entitySystem)
	:BaseSystem(),
	entitySystem_(entitySystem),
	processedComp_(0){
}

//void AISystem::addComponent(unsigned int ID, AIComponent& component){
//	assert(components_.count(ID) == 0 && "Component already exsists!");
//	for (auto& bhvr : component.behaviours_)
//		bhvr->setObserver(this);
//	components_.emplace(ID, component);
//}

void AISystem::update(const sf::Time& dt){
	for (auto& comp : components_){
		processedComp_ = comp.first;
		comp.second.behaviours_.at(comp.second.currentBehaviour_)->update(dt);
	}
}

void AISystem::onEntityEvent(){
	AIComponent& ai = components_.at(processedComp_);
	unsigned int& currentAiBhvr = ai.currentBehaviour_;

	//get event from currently processed behaviour
	EntityEvent ev = ai.behaviours_.at(currentAiBhvr)->getEvent();

	//append unique ID of entity that generated event
	ev.uid_ = processedComp_; //not needed?

	//push this event into EntitySystem's event queue
	entitySystem_.pushEvent(ev);

	//change ai's current behaviour
	if (++currentAiBhvr >= ai.behaviours_.size())
		currentAiBhvr = 0;
}
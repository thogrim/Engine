#pragma once

#include <vector>
#include <SFML/System/Time.hpp>
#include "../EntityEvent.h"

class EntityBehaviourObserver;

class EntityBehaviour{
public:
	//EntityBehaviour(std::initializer_list<EntityEvent> events);
	EntityBehaviour(const std::vector<EntityEvent>& events);
	EntityBehaviour(const EntityEvent& ev);
	virtual ~EntityBehaviour();
	void setObserver(EntityBehaviourObserver* observer);
	//void setEvent(const EntityEvent& ev);
	std::vector<EntityEvent>& getEvents();
	virtual void update(const sf::Time& dt) = 0;
protected:
	void notifyObserver();
	//EntityEvent event_;
	std::vector<EntityEvent> events_;
private:
	EntityBehaviourObserver* observer_;
};
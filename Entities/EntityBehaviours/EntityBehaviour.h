#pragma once

#include <SFML/System/Time.hpp>
#include "../EntityEvent.h"

class EntityBehaviourObserver;

class EntityBehaviour{
public:
	EntityBehaviour(const EntityEvent& ev);
	virtual ~EntityBehaviour();
	void setObserver(EntityBehaviourObserver* observer);
	//void setEvent(const EntityEvent& ev);
	const EntityEvent& getEvent() const;
	virtual void update(const sf::Time& dt) = 0;
protected:
	void notifyObserver();
	EntityEvent event_;
private:
	EntityBehaviourObserver* observer_;
};
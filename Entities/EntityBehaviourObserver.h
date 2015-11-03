#pragma once

//class EntityEvent;

class EntityBehaviourObserver{
public:
	virtual ~EntityBehaviourObserver(){}
	virtual void onEntityEvent(/*const EntityEvent& ev*/) = 0;
};
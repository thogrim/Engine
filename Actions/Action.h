/***********************************
	Interface for Action classes
************************************/

#pragma once

#include <cassert>
#include <SFML/System/Time.hpp>

class ActionObserver;

class Action{
public:
	Action(ActionObserver* obs = nullptr);
	virtual ~Action();
	virtual void update(const sf::Time& dt)=0;
	void setObserver(ActionObserver* obs);
protected:
	virtual void updateAction(const sf::Time& dt) = 0;

	ActionObserver* observer_;
};
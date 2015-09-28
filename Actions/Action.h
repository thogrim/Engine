/***************************************************
	Interface for Action classes

	IMPORTANT:
	all actions must implement clone method
	to allow copying it(prototype pattern)
	like this:

	Action* MyAction::clone() const{
		return new MyAction(*this);
	}

****************************************************/

#pragma once

#include <SFML/System/Time.hpp>

class ActionObserver;

class Action{
public:
	Action(ActionObserver& obs, const sf::Time& duration);
	virtual ~Action();
	void update(const sf::Time& dt);
	virtual Action* clone() const = 0;
	//to delete
	//void reset();
protected:
	virtual void updateAction(const sf::Time& dt) = 0;
	//void notifyCompletion();
	sf::Time timeLeft_;
private:
	ActionObserver& observer_;
};
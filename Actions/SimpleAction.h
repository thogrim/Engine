/***************************************************
	Interface for Action classes

	IMPORTANT:
	it is necessary that update() method checks
	whether an action has finished and if it has,
	it needs to call notifyCompletion() to let
	the observer process that information:

	void MyAction::update(const sf::Time& dt){
		//...
		//update action
		//..

		//checking completion:
		timeLeft_ -= dt;
		if (timeLeft_ < sf::Time::Zero)
			notifyCompletion();
	}

	all actions must also implement clone method
	to allow copying it(prototype pattern)
	like this:

	SimpleAction* MyAction::clone() const{
		return new MyAction(*this);
	}

****************************************************/

#pragma once

#include <SFML/System/Time.hpp>

class ActionObserver;

namespace Action{
	class SimpleAction{
	public:
		SimpleAction(ActionObserver& obs, const sf::Time& duration);
		virtual ~SimpleAction();
		virtual void update(const sf::Time& dt) = 0;
		virtual SimpleAction* clone() const = 0;
		//to delete
		void reset();
	protected:
		void notifyCompletion();
		sf::Time timeLeft_;
	private:
		ActionObserver& observer_;
	};
}
#pragma once

#include "Action.h"

namespace Actions{
	class SimpleAction : public Action{
	public:
		SimpleAction(/*ActionObserver* obs = nullptr,*/ const sf::Time& duration);
		virtual ~SimpleAction();
		void update(const sf::Time& dt);
	protected:
		virtual void updateAction(const sf::Time& dt) = 0;
	private:
		sf::Time initialTime_;
		sf::Time timeLeft_;
	};
}
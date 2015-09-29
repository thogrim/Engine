#pragma once

//#include <iostream>
#include <vector>
#include "../ActionObserver.h"
#include "Action.h"

namespace Actions{
	class CompositeAction : public Action, public ActionObserver{
	public:
		CompositeAction(ActionObserver* obs);
		CompositeAction(const CompositeAction& comp);
		~CompositeAction();
		void addAction(Action* a);
		void update(const sf::Time& dt);
		void onActionFinish();
	private:
		void updateAction(const sf::Time& dt);
		std::vector<std::pair<Action*,bool>> actions_;
		unsigned int currentAction_;
		unsigned int finishedActions_;
	};
}
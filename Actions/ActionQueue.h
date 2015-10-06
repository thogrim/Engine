#pragma once

#include <vector>
#include <cassert>
#include "../ActionObserver.h"
#include "Action.h"

namespace Actions{
	class ActionQueue : public Action, public ActionObserver{
	public:
		ActionQueue();
		~ActionQueue();
		void addAction(Action* a);
		void update(const sf::Time& dt);
		void onActionFinish();
	private:
		void updateAction(const sf::Time& dt);
		std::vector<Action*> actions_;
		unsigned int currentAction_;
	};
}
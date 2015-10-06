#pragma once

#include <cassert>
#include "Action.h"

namespace Actions{
	class InstantAction : public Action{
	public:
		InstantAction();
		virtual ~InstantAction();
		void update(const sf::Time& dt);
	protected:
		virtual void updateAction(const sf::Time& dt) = 0;
	};
}
#pragma once

#include <SFML/System/Time.hpp>
//#include "../States/State.h"

namespace Actions{
	class Action{
	public:
		Action();
		virtual ~Action();
		virtual void update(const sf::Time& dt) = 0;
		bool done() const;
	protected:
		bool done_;
	};
}
#pragma once

#include "../InstantAction.h"

namespace GUI{
	class Menu;
}

namespace Actions{
	class SetActive: public InstantAction{
	public:
		SetActive(GUI::Menu& menu, bool activation);
		~SetActive();
	private:
		void updateAction(const sf::Time& dt);
		GUI::Menu& menu_;
		bool activation_;
	};
}
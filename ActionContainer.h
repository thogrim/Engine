#pragma once

#include <cassert>

class Action;

class ActionContainer{
public:
	ActionContainer();
	virtual ~ActionContainer();
	void storeAction(Action* action);
	Action* getAction() const;
private:
	Action* action_;
};


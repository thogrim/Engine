#pragma once

#include <cassert>

class Action;

class ActionContainer{
public:
	ActionContainer();
	virtual ~ActionContainer();
	void storeAction(Action* action);
	Action* getAction() const;
protected:
	Action* action_;
};


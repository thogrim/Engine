/************************************
	Interface for action observers
*************************************/

#pragma once

class ActionObserver{
public:
	ActionObserver();
	virtual ~ActionObserver();

	//method performed when action
	//notifies about its completion
	virtual void onActionFinish() = 0;
};
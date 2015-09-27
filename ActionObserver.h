#pragma once

class ActionObserver{
public:
	ActionObserver();
	virtual ~ActionObserver();
	virtual void onActionFinish() = 0;
};
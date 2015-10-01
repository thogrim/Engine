#pragma once

namespace GUI{
	class Component;
}

class GuiObserver{
public:
	GuiObserver();
	virtual ~GuiObserver();
	//method performed when mouse is released
	virtual void onGuiComponentReleased(const GUI::Component& component)=0;
};


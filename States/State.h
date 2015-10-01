#pragma once

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Application.h"
#include "../ActionObserver.h"
#include "../GUI/GuiObserver.h"
#include "../ActionContainer.h"

class Action;

class State: public GuiObserver, public sf::Drawable, public ActionObserver{
public:
	State(Application& app);
	State(const State& state);
	virtual ~State();

protected:
	//method called at the end of constructor
	//to avoid duplicate code in:
	//MyState(Application& app)
	//MyState(const State& state)
	virtual void init()=0;
	//stores action a in container ac
	void storeAction(ActionContainer& ac, Action* a);
	//registers action, that causes state change
	void addStateChangeCallback(const ActionContainer& ac, std::function<State*()> changeFunction);
	//sets state to perform action from
	//provided action container
	void setAction(const ActionContainer& ac);

public:
	//method performed when action has ended
	void onActionFinish() override;
	//method performed when GUI component was released correctly
	void onGuiComponentReleased(const GUI::Component& component);
	//method performed when key is pressed
	virtual void onKeyPressed(sf::Keyboard::Key key)=0;
	//method performed when window is resized
	virtual void onResized(const sf::Event::SizeEvent& size) = 0;
	//method performed when mouse button is pressed
	virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton) = 0;
	//method performed when mouse button is released
	virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton) = 0;
	//method performed when mouse is moving
	virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove) = 0;
	//virtual void onAnotherEventType()=0;

protected:
	//this update is executed regardless of
	//state's current action
	virtual void withActionUpdate(const sf::Time& dt) = 0;
	//this update is executed when there is no
	//action for state to perform currently
	virtual void noActionUpdate(const sf::Time& dt) = 0;

public:
	void update(const sf::Time& dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	//other helpful methods

	//get application's console
	std::ostringstream& getAppConsole();
	//get mouse position relative to view
	sf::Vector2f getMousePos(const sf::View& view);

private:
	//Reference to application
	Application& app_;
	//current action to perform
	Action* action_;
	//container holding pointers to actions that cause state to change
	typedef std::pair < Action*, std::function<State*()>> StateChangeCallback;
	std::vector<StateChangeCallback> stateChangeCallbacks_;
protected:
	sf::View camera_;
};
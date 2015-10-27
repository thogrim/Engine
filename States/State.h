#pragma once

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Application.h"
#include "../ActionObserver.h"
#include "../GUI/GuiObserver.h"
#include "../ActionContainer.h"

class Action;
class StateBehaviour;

class State: public GuiObserver, public sf::Drawable, public ActionObserver{
public:
	State(Application& app);
	//State(const State& state);
	virtual ~State();

protected:
	//method called at the end of constructor
	//to avoid duplicate code in:
	//MyState(Application& app)
	//MyState(const State& state)
	//virtual void init()=0;

	//stores action a in container ac
	void storeAction(ActionContainer& ac, Action* a);
	//stores action a in GUI component
	void storeAction(GUI::Component& comp, Action* a);
	//registers action, that causes state change
	void addStateChangeCallback(const ActionContainer& ac, std::function<State*()> changeFunction);
	//registers action, that causes behaviour change
	void addBehaviourChangeCallback(const ActionContainer& ac, std::function<StateBehaviour*()> changeFunction);
	//sets state to perform action from
	//provided action container
	void setAction(const ActionContainer& ac);
	//sets current behaviour
	//void setBehaviour(StateBehaviour* newBehaviour);

public:
	//method performed when action has ended
	void onActionFinish() override;
	//method performed when GUI component was released correctly
	void onGuiComponentReleased(const GUI::Component& component);
	//method performed when key is pressed
	virtual void onKeyPressed(sf::Keyboard::Key key);
	//method performed when key is released
	virtual void onKeyReleased(sf::Keyboard::Key key);
	//method performed when window is resized
	virtual void onResized(const sf::Event::SizeEvent& size) = 0;
	//method performed when mouse button is pressed
	virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton);
	//method performed when mouse button is released
	virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton);
	//method performed when mouse is moving
	virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove);
	//virtual void onAnotherEventType()=0;

protected:
	//this update is executed regardless of
	//state's current action
	virtual void withActionUpdate(const sf::Time& dt) = 0;
	//this update is executed when there is no
	//action for state to perform currently
	virtual void noActionUpdate(const sf::Time& dt);

public:
	void update(const sf::Time& dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	//other helpful methods

	//get application's console
	//std::ostringstream& getAppConsole();
	//get mouse position relative to view
	sf::Vector2f getMousePos(const sf::View& view);

	//Reference to application
	Application& app_;

private:
	//current action to perform
	Action* action_;

protected:
	//current behaviour
	StateBehaviour* behaviour_;

private:
	//container holding pointers to actions that cause state to change
	typedef std::pair < Action*, std::function<State*()>> StateChangeCallback;
	std::vector<StateChangeCallback> stateChangeCallbacks_;
	//container holding pointers to actions that cause behaviour to change
	typedef std::pair < Action*, std::function<StateBehaviour*()>> BehaviourChangeCallback;
	std::vector<BehaviourChangeCallback> behaviourChangeCallbacks_;
protected:
	sf::View camera_;
};
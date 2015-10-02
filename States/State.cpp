#include "State.h"
#include "../Actions/Action.h"
#include "../GUI/Component.h"

State::State(Application& app)
	:app_(app),
	action_(nullptr),
	stateChangeCallbacks_(),
	camera_(app_.getWindow().getView()){
}

State::State(const State& state)
	:app_(state.app_),
	action_(nullptr),
	stateChangeCallbacks_(),
	camera_(app_.getWindow().getView()){
}

State::~State(){
}

void State::storeAction(ActionContainer& ac, Action* a){
	a->setObserver(this);
	ac.storeAction(a);
}

void State::storeAction(GUI::Component& comp, Action* a){
	a->setObserver(this);
	comp.setObserver(this);
	comp.storeAction(a);
}

void State::addStateChangeCallback(const ActionContainer& ac, std::function<State*()> changeFunction){
	stateChangeCallbacks_.emplace_back(ac.getAction(), changeFunction);
}

void State::setAction(const ActionContainer& ac){
	//dont set new action when there is still
	//action to perform
	if (!action_)
		action_ = ac.getAction();
}

void State::onActionFinish(){
	//check if performed action cause state change
	auto it = std::find_if(stateChangeCallbacks_.begin(), stateChangeCallbacks_.end(),
		[this](const StateChangeCallback& callback){
		return  callback.first == action_;
	});

	//if it does, change state
	if (it != stateChangeCallbacks_.end()){
		action_ = nullptr;
		app_.changeState(it->second());
	}

	//else remove action
	else
		action_ = nullptr;
}

void State::onGuiComponentReleased(const GUI::Component& component){
	setAction(component);
}

void State::update(const sf::Time& dt){
	withActionUpdate(dt);
	if (action_){
		app_.getConsole() << "Performing action\n";
		action_->update(dt);
	}
	else
		noActionUpdate(dt);
}

std::ostringstream& State::getAppConsole(){
	return app_.getConsole();
}

sf::Vector2f State::getMousePos(const sf::View& view){
	//get window mouse pos
	sf::Vector2i mousePos = sf::Mouse::getPosition(app_.getWindow());
	//store current view
	sf::View currentView = app_.getWindow().getView();
	//set window's view
	app_.getWindow().setView(view);
	//get mouse pos relative to view
	sf::Vector2f mousePosInView = app_.getWindow().mapPixelToCoords(mousePos);
	//restore current view
	app_.getWindow().setView(currentView);

	return mousePosInView;
}
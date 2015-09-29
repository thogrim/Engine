#include "State.h"
//#include "../Application.h"
#include "../Actions/Action.h"

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

//void State::requestChange(State* state){
//	app_.changeState(state);
//}

void State::addStateChangeCallback(const ActionContainer& ac, std::function<State*()> changeFunction){
	stateChangeCallbacks_.emplace_back(ac.getAction(), changeFunction);
}

void State::setAction(ActionContainer& ac){
	//dont set new action when there is still
	//action to perform
	if (action_)
		return;

	action_ = ac.getAction();
	//check if action changes state
	//auto it = std::find_if(stateChangeCallbacks_.begin(), stateChangeCallbacks_.end(),
	//	[action](const StateChangeCallback& callback){
	//	return  callback.first == action;
	//});

	////if it does, let it perform
	//if (it != stateChangeCallbacks_.end())
	//	action_ = action;

	////else copy action, and perform its copy
	//else
	//	action_ = action->clone();
}

void State::onActionFinish(){
	//check if performed action cause state change
	auto it = std::find_if(stateChangeCallbacks_.begin(), stateChangeCallbacks_.end(),
		[this](const StateChangeCallback& callback){
		return  callback.first == action_;
	});

	//if it does, change state
	if (it != stateChangeCallbacks_.end())
		app_.changeState(it->second());

	//else remove action
	else
		action_ = nullptr;
}

void State::update(const sf::Time& dt){
	withActionUpdate(dt);
	if (action_)
		action_->update(dt);
	else
		noActionUpdate(dt);

	if (action_)
		app_ << "Performing action\n";
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
#include "State.h"
#include "StateBehaviour.h"
#include "../Actions/Action.h"
#include "../GUI/Component.h"

State::State(Application& app)
	:app_(app),
	action_(nullptr),
	behaviour_(nullptr),
	stateChangeCallbacks_(),
	behaviourChangeCallbacks_(),
	camera_(app_.getWindow().getView()){
}

//State::State(const State& state)
//	:app_(state.app_),
//	action_(nullptr),
//	behaviour_(nullptr),
//	stateChangeCallbacks_(),
//	behaviourChangeCallbacks_(),
//	camera_(app_.getWindow().getView()){
//}

State::~State(){
	delete behaviour_;
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

void State::addBehaviourChangeCallback(const ActionContainer& ac, std::function<StateBehaviour*()> changeFunction){
	behaviourChangeCallbacks_.emplace_back(ac.getAction(), changeFunction);
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

	//else check behaviour change functions
	else{
		auto it2 = std::find_if(behaviourChangeCallbacks_.begin(), behaviourChangeCallbacks_.end(),
			[this](const BehaviourChangeCallback& callback){
			return  callback.first == action_;
		});

		//change behaviour
		if (it2 != behaviourChangeCallbacks_.end()){
			action_ = nullptr;
			delete behaviour_;
			behaviour_ = it2->second();
		}
		
		else
			action_ = nullptr;
	}
}

void State::onGuiComponentReleased(const GUI::Component& component){
	setAction(component);
}

void State::onKeyPressed(sf::Keyboard::Key key){
	assert(behaviour_);
	behaviour_->onKeyPressed(key);
}

void State::onKeyReleased(sf::Keyboard::Key key){
	assert(behaviour_);
	behaviour_->onKeyReleased(key);
}

void State::onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton){
	assert(behaviour_);
	behaviour_->onMouseButtonPressed(mouseButton);
}

void State::onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton){
	assert(behaviour_);
	behaviour_->onMouseButtonReleased(mouseButton);
}

void State::onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove){
	assert(behaviour_);
	behaviour_->onMouseMoved(mouseMove);
}

void State::noActionUpdate(const sf::Time& dt){
	assert(behaviour_);
	behaviour_->update(dt);
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

void State::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.setView(camera_);
	target.draw(*behaviour_);
}

//std::ostringstream& State::getAppConsole(){
//	return app_.getConsole();
//}

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
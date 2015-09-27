#include "State.h"
#include "../Application.h"
#include "../Actions/SimpleAction.h"

State::State(Application& app)
	:app_(app),
	action_(nullptr),
	camera_(app_.getWindow().getView()){
}

State::~State(){
}

void State::loadResources(){
	try{
		loadTextures();
		loadFonts();
		loadSound();
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
}

void State::setAction(Action::SimpleAction* action){
	action_ = action;
	//if (!action_)
	//	action_ = action->clone();
}
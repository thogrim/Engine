#include "State.h"
#include "../Application.h"
#include "../Actions/Action.h"

State::State(Application& app)
	:app_(app),
	action_(nullptr),
	camera_(app_.getWindow().getView()){
}

State::~State(){
}

//void State::loadResources(){
//	try{
//		loadTextures();
//		loadFonts();
//		loadSound();
//	}
//	catch (std::runtime_error& e){
//		std::cout << e.what() << std::endl;
//	}
//}

//method not needed; 
void State::setAction(Action* action){
	action_ = checkEnterStateActions(action);
}

//void State::changeState(State* state){
//	delete action
//}
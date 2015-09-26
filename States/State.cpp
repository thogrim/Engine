#include "State.h"
#include "../Application.h"

State::State(Application& app)
	:app_(app),
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
#include "State.h"

State::State()
	:camera_(),
	textures_(),
	fonts_(){
}

State::~State(){
}

void State::init(){
	try{
		loadTextures();
		loadFonts();
		loadSound();
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
}
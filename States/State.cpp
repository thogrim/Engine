#include "State.h"

State::State(){
}

State::~State(){
}

void State::init(){
	loadTextures();
	loadFonts();
	loadSound();
}
#include "TitleState.h"

TitleState::TitleState()
	:State(){
}

TitleState::~TitleState(){
}

void TitleState::loadTextures(){
}

void TitleState::loadFonts(){
}

void TitleState::loadSound(){
}

void TitleState::processKeyPressed(sf::Keyboard::Key key){
	if (key == sf::Keyboard::R)
		world_.resetCamera();
}

void TitleState::update(const sf::Time& dt){
	world_.update(dt);
}

void TitleState::render() const{
	Context::instance().window_.draw(world_);
}
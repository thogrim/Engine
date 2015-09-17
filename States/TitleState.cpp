#include "TitleState.h"

TitleState::TitleState()
	:State(){
	init();
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
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	case sf::Keyboard::Return:
		Context::instance().changeState(new GameState());
		break;
	}
}

void TitleState::processResized(const sf::Event::SizeEvent& size){
	world_.resizeCamera(size.width, size.height);
}

void TitleState::update(const sf::Time& dt){
	world_.update(dt);
}

void TitleState::render() const{
	Context::instance().window_.draw(world_);
}
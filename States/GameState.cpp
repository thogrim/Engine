#include "GameState.h"

GameState::GameState()
	:State(){
}

GameState::~GameState(){
}

void GameState::loadTextures(){
}

void GameState::loadFonts(){
}

void GameState::loadSound(){
}

void GameState::processKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	case sf::Keyboard::Return:
		Context::instance().changeState(new TitleState());
		break;
	}
}

void GameState::processResized(const sf::Event::SizeEvent& size){
	world_.resizeCamera(size.width, size.height);
}

void GameState::update(const sf::Time& dt){
	world_.update(dt);
}

void GameState::render() const{
	Context::instance().window_.draw(world_);
}

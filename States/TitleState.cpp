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

void TitleState::update(const sf::Time& dt){
}

void TitleState::render() const{
	sf::CircleShape shape(30.f,20);
	shape.setPosition(500.f, 500.f);
	shape.setFillColor(sf::Color(112,134,65));
	Context::instance().window_.draw(shape);
	//Context::instance().window_.clear();
}
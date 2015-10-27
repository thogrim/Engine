#include "ChooseLevelBehaviour.h"
#include "../../GUI/Menu.h"

ChooseLevelBehaviour::ChooseLevelBehaviour(GUI::Menu& levelMenu)
	:StateBehaviour(),
	levelMenu_(levelMenu){
}

ChooseLevelBehaviour::~ChooseLevelBehaviour(){
}

void ChooseLevelBehaviour::onKeyPressed(sf::Keyboard::Key key){
	//do nothing for now
}

void ChooseLevelBehaviour::onKeyReleased(sf::Keyboard::Key key){
	//do nothing for now
}

void ChooseLevelBehaviour::onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton){
	levelMenu_.onMouseButtonPressed(mouseButton);
}

void ChooseLevelBehaviour::onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton){
	levelMenu_.onMouseButtonReleased(mouseButton);
}

void ChooseLevelBehaviour::onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove){
	levelMenu_.onMouseMoved(mouseMove);
}

void ChooseLevelBehaviour::update(const sf::Time& dt){
	//do nothing for now
}

void ChooseLevelBehaviour::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(levelMenu_);
}
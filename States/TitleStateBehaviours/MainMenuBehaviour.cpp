#include "MainMenuBehaviour.h"
#include "../../GUI/Menu.h"

MainMenuBehaviour::MainMenuBehaviour(GUI::Menu& mainMenu)
	:StateBehaviour(),
	mainMenu_(mainMenu){
}

MainMenuBehaviour::~MainMenuBehaviour(){
}

void MainMenuBehaviour::onKeyPressed(sf::Keyboard::Key key){
	//do nothing for now
}

void MainMenuBehaviour::onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton){
	mainMenu_.onMouseButtonPressed(mouseButton);
}

void MainMenuBehaviour::onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton){
	mainMenu_.onMouseButtonReleased(mouseButton);
}

void MainMenuBehaviour::onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove){
	mainMenu_.onMouseMoved(mouseMove);
}

void MainMenuBehaviour::update(const sf::Time& dt){
	//do nothing for now
}

void MainMenuBehaviour::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mainMenu_);
}
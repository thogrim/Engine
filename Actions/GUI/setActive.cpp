#include "SetActive.h"
#include "../../GUI/Menu.h"

using namespace Actions;

SetActive::SetActive(GUI::Menu& menu, bool activation)
	:menu_(menu),
	activation_(activation){
}

SetActive::~SetActive(){
}

void SetActive::updateAction(const sf::Time& dt){
	menu_.setActive(activation_);
}
#include "Component.h"
#include "GuiObserver.h"

using namespace GUI;

Component::Component()
	:sprite_(),
	hovered_(false),
	pressed_(false),
	parent_(nullptr),
	observer_(nullptr){
}

Component::~Component(){
}

void Component::setObserver(GuiObserver* obs){
	observer_ = obs;
}

void Component::setTexture(const sf::Texture& texture){
	sprite_.setTexture(texture, true);//true resets TextureRect to texture's size
}

void Component::setParent(Component* parent){
	parent_ = parent;
}

void Component::onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton){
	if (mouseButton.button == sf::Mouse::Button::Left){
		if (hovered_)
			pressed_ = true;
			//onPressed()
	}
}

void Component::onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton){
	if (mouseButton.button == sf::Mouse::Button::Left){
		if (hovered_ && pressed_){
			//notify observer
			observer_->onGuiComponentReleased(*this);
		}
		pressed_ = false;
		//onRelease();
	}
}

//To refactor
void Component::onMouseMoved(sf::Event::MouseMoveEvent mouseMove){
	mouseMove.x -= getPosition().x;
	mouseMove.y -= getPosition().y;
	//smth like that
	if (sprite_.getLocalBounds().contains(mouseMove.x, mouseMove.y)){
		if (!hovered_){
			hovered_ = true;
			//and maybe set sprite to hovered sprite
			//use pure virtual method like
			//onMouseEnter()
		}
	}
	else{
		if (hovered_){
			hovered_ = false;
			//onMouseLeave();
		}
	}
}


void Component::update(const sf::Time& dt){
	//animation update
}

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(sprite_, states);
}
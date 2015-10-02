#include "Component.h"
#include "GuiObserver.h"

using namespace GUI;

Component::Component()
	:sprite_(),
	text_(),
	hovered_(false),
	pressed_(false),
	//parent_(nullptr),
	observer_(nullptr){
}

Component::~Component(){
}

void Component::setTexture(const sf::Texture& texture){
	sprite_.setTexture(texture, true);
}

void Component::setText(const std::string& string, const sf::Font& font, unsigned int characterSize){
	text_.setString(string);
	text_.setFont(font);
	text_.setCharacterSize(characterSize);
}

void Component::setTextPosition(float x, float y){
	text_.setPosition(x, y);
}

void Component::setObserver(GuiObserver* obs){
	observer_ = obs;
}

const sf::FloatRect& Component::getSize() const{
	return sprite_.getLocalBounds();
}

bool Component::hovered() const{
	return hovered_;
}

//void Component::setParent(Component* parent){
//	parent_ = parent;
//}

void Component::onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton){
	if (mouseButton.button == sf::Mouse::Button::Left){
		if (hovered_){
			pressed_ = true;
			onSpritePressed();
		}
	}
}

void Component::onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton){
	if (mouseButton.button == sf::Mouse::Button::Left){
		if (hovered_ && pressed_){
			//notify observer
			observer_->onGuiComponentReleased(*this);
		}
		onSpriteReleased();
		pressed_ = false;
	}
}

//TODO
void Component::onMouseMoved(sf::Event::MouseMoveEvent mouseMove){
	mouseMove.x -= getPosition().x;
	mouseMove.y -= getPosition().y;
	//smth like that
	if (sprite_.getLocalBounds().contains(mouseMove.x, mouseMove.y)){
		if (!hovered_){
			hovered_ = true;
			onMouseEnter();
		}
	}
	else{
		if (hovered_){
			hovered_ = false;
			onMouseLeave();
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
#include "Button.h"

using namespace GUI;

Button::Button()
	:Component(){
}

Button::~Button(){
}

void Button::setTexture(const sf::Texture& texture){
	int width = texture.getSize().x;
	int height = texture.getSize().y / 3;
	normalRect_ = sf::IntRect(0, 0, width, height);
	hoveredRect_ = sf::IntRect(0, height, width, height);
	pressedRect_ = sf::IntRect(0, 2 * height, width, height);
	sprite_.setTexture(texture);
	sprite_.setTextureRect(normalRect_);
}

void Button::onMouseEnter(){
	if (!pressed_)
		sprite_.setTextureRect(hoveredRect_);
}

void Button::onMouseLeave(){
	if (!pressed_)
		sprite_.setTextureRect(normalRect_);
}

void Button::onSpritePressed(){
	sprite_.setTextureRect(pressedRect_);
}

void Button::onSpriteReleased(){
	hovered_ ? sprite_.setTextureRect(hoveredRect_) : sprite_.setTextureRect(normalRect_);
}
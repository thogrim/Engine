#include "Menu.h"
#include "Component.h"

using namespace GUI;

Menu::Menu()
	:sprite_(),
	text_(),
	components_(),
	hoveredComponent_(nullptr),
	pressedComponent_(nullptr),
	active_(true){
}

Menu::~Menu(){
	for (Component* c : components_)
		delete c;
}

void Menu::addComponent(Component* c){
	components_.push_back(c);
}

void Menu::setTexture(const sf::Texture& texture){
	sprite_.setTexture(texture, true);
}

void Menu::setText(const std::string& string, const sf::Font& font, unsigned int characterSize){
	text_.setString(string);
	text_.setFont(font);
	text_.setCharacterSize(characterSize);
}

void Menu::setTextPosition(float x, float y){
	text_.setPosition(x, y);
}

void Menu::setActive(bool active){
	active_ = active;
	for (Component* c : components_)
		c->active_ = active;
}

//void Menu::setColor(sf::Color color){
//	sprite_.setColor(color);
//}

//sf::Sprite& Menu::getSprite(){
//	return sprite_;
//}
//
//std::vector<Component*>& Menu::getComponents(){
//	return components_;
//}

void Menu::onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton){
	if(active_ && hoveredComponent_){
		hoveredComponent_->onMouseButtonPressed(mouseButton);
		if (hoveredComponent_->pressed_)
			pressedComponent_ = hoveredComponent_;
	}
}

void Menu::onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton){
	if (active_ && pressedComponent_){
		pressedComponent_->onMouseButtonReleased(mouseButton);
		if (!pressedComponent_->pressed_)
			pressedComponent_ = nullptr;
	}
	//if (hoveredComponent_){
	//	hoveredComponent_->onMouseButtonReleased(mouseButton);
	//}
}

void Menu::onMouseMoved(sf::Event::MouseMoveEvent mouseMove){
	if (!active_)
		return;
	mouseMove.x -= getPosition().x;
	mouseMove.y -= getPosition().y;
	//bool mouseInMenu = sprite_.getLocalBounds().contains(mouseMove.x, mouseMove.y);
	if (hoveredComponent_){
		hoveredComponent_->onMouseMoved(mouseMove);
			if (!hoveredComponent_->hovered_)
				hoveredComponent_ = nullptr;
		//can mouse move be fast enough that overs instantly
		//over other component? if yes then i should check for
		//hovering other components; for now i assume it cannot
	}
	else{
		if (sprite_.getLocalBounds().contains(mouseMove.x, mouseMove.y)){
			auto it = std::find_if(components_.begin(), components_.end(), [mouseMove](const Component* c){
						return c->sprite_.getLocalBounds().contains(mouseMove.x - c->getPosition().x, mouseMove.y - c->getPosition().y);
					});
			if (it != components_.end()){
				hoveredComponent_ = *it;
				hoveredComponent_->onMouseMoved(mouseMove);
			}
		}
	}
}

void Menu::update(const sf::Time& dt){
	if (active_)
	for (Component* c : components_)
		c->update(dt);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//if (!active_)
	//	return;
	states.transform *= getTransform();
	//states.shader = shader;
	target.draw(sprite_, states);
	for (const Component* c : components_)
		target.draw(*c, states);
}
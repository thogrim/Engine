#include "Player.h"
#include "Components/CollisionComponent.h"

Player::Player()
	:hitbox_(sf::Vector2f(54.f,96.f)),
	playerTex_(nullptr),
	sprite_(),
	velocity_(0.f,0.f),
	playerVel_(200.f){
	playerTex_ = new sf::Texture();
	if (!playerTex_->loadFromFile("res/img/Player.png")){
		//
	}
	sprite_.setTexture(*playerTex_);
	//setOrigin(27.f, 48.f);
	//hitbox_.setOutlineColor(sf::Color::Magenta);
	//hitbox_.setOutlineThickness(10.f);
	hitbox_.setFillColor(sf::Color(255, 0, 255, 128));
}

Player::~Player(){
	delete playerTex_;
}

void Player::onKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::Up:
		velocity_.y = -playerVel_;
		break;
	case sf::Keyboard::Right:
		velocity_.x = playerVel_;
		break;
	case sf::Keyboard::Down:
		velocity_.y = playerVel_;
		break;
	case sf::Keyboard::Left:
		velocity_.x = -playerVel_;
		break;
	}
}

void Player::onKeyReleased(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::Up:
		if (velocity_.y != playerVel_) velocity_.y = 0.f;
		break;
	case sf::Keyboard::Right:
		if (velocity_.x != -playerVel_) velocity_.x = 0.f;
		break;
	case sf::Keyboard::Down:
		if (velocity_.y != -playerVel_) velocity_.y = 0.f;
		break;
	case sf::Keyboard::Left:
		if (velocity_.x != playerVel_) velocity_.x = 0.f;
		break;
	}
}

const VisitableRectangleShape& Player::getShape() const{
	return hitbox_;
}

const sf::Vector2f& Player::getMiddle() const{
	return getPosition() + sf::Vector2f(hitbox_.getLocalBounds().width/2, hitbox_.getLocalBounds().height/2);
}

void Player::update(const sf::Time& dt){
	move(velocity_*dt.asSeconds());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform = getTransform();
	target.draw(sprite_, states);
	target.draw(hitbox_, states);
}
#include "GameState.h"
#include "TitleState.h"
#include "../Actions/Transforms.h"

GameState::GameState(Application& app)
	:State(app),
	world_(),
	shape_(sf::Vector2f(100.f, 150.f)),
	ac_(),
	ac2_(),
	ac3_(){
	init();
}

GameState::GameState(const State& state)
	:State(state),
	world_(),
	shape_(sf::Vector2f(100.f, 150.f)),
	ac_(),
	ac2_(){
	init();
}

GameState::~GameState(){
}

void GameState::init(){
	world_.setCamera(camera_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setPosition(450.f, 300.f);

	storeAction(ac_, new Actions::Rotate(sf::seconds(1.f), shape_, 360.f));

	storeAction(ac2_, new Actions::Rotate(sf::seconds(1.f), shape_, -360.f));

	storeAction(ac3_, new Actions::Rotate(sf::seconds(1.f), shape_, 45.f));

	addStateChangeCallback(ac3_, [this](){
		return new TitleState(*this);
	});
}

void GameState::onKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	case sf::Keyboard::Num1:
		setAction(ac_);
		break;
	case sf::Keyboard::Num2:
		setAction(ac2_);
		break;
	case sf::Keyboard::B:
		setAction(ac3_);
		break;
	}
}

void GameState::onResized(const sf::Event::SizeEvent& size){
	float dwidth = size.width - camera_.getSize().x;
	float dheight = size.height - camera_.getSize().y;
	camera_.move(dwidth / 2, dheight / 2);
	camera_.setSize(static_cast<float>(size.width), static_cast<float>(size.height));
	world_.resizeCamera(size.width, size.height);
}

void GameState::onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton){

}
void GameState::onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton){

}
void GameState::onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove){

}

void GameState::withActionUpdate(const sf::Time& dt){
	sf::Vector2f worldMousePos = getMousePos(world_.getCamera());
	getAppConsole() << "World's mouse position: " << worldMousePos.x << " " << worldMousePos.y << std::endl
		<< "Current world zoom: " << world_.getZoom() << std::endl;
}

void GameState::noActionUpdate(const sf::Time& dt){
	//update world
	world_.update(dt);
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//set camera
	target.setView(camera_);

	//draw
	target.draw(world_);
	target.draw(shape_);
}
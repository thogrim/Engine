#include "TitleState.h"
#include "GameState.h"
#include "../Actions/MoveBy.h"

TitleState::TitleState(Application& app)
	:State(app),
	world_(),
	shape_(sf::Vector2f(100.f,100.f)),
	ac_(),
	ac2_(){
	world_.setCamera(camera_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setPosition(450.f, 250.f);
	ac_.storeAction(new Actions::MoveBy(*this, sf::seconds(2.f), shape_, 300.f, 0.f));
	auto call1 = [this](){
		return new GameState(*this);
	};
	addStateChangeCallback(ac_, call1);
	ac2_.storeAction(new Actions::MoveBy(*this, sf::seconds(2.f), shape_, -300.f, 0.f));
}

TitleState::TitleState(const State& state)
	:State(state),
	world_(),
	shape_(sf::Vector2f(100.f, 100.f)),
	ac_(),
	ac2_(){
	world_.setCamera(camera_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setPosition(450.f, 250.f);
	ac_.storeAction(new Actions::MoveBy(*this, sf::seconds(2.f), shape_, 300.f, 0.f));
	auto call1 = [this](){
		return new GameState(*this);
	};
	addStateChangeCallback(ac_, call1);
	ac2_.storeAction(new Actions::MoveBy(*this, sf::seconds(2.f), shape_, -300.f, 0.f));
}

TitleState::~TitleState(){
}

void TitleState::onKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	case sf::Keyboard::Num1:
		setAction(ac_.getAction());
		break;
	case sf::Keyboard::Num2:
		setAction(ac2_.getAction());
		break;
	}
}

void TitleState::onResized(const sf::Event::SizeEvent& size){
	//resize state's camera
	float dwidth = size.width - camera_.getSize().x;
	float dheight = size.height - camera_.getSize().y;
	camera_.move(dwidth / 2, dheight / 2);
	camera_.setSize(static_cast<float>(size.width), static_cast<float>(size.height));

	//resize world camera
	world_.resizeCamera(size.width, size.height);
}

void TitleState::withActionUpdate(const sf::Time& dt){
	sf::Vector2f worldMousePos = getMousePos(world_.getCamera());
	getAppConsole() << "World's mouse position: " << worldMousePos.x << " " << worldMousePos.y << std::endl
		<< "Current world zoom: " << world_.getZoom() << std::endl;
}

void TitleState::noActionUpdate(const sf::Time& dt){
	//update world
	world_.update(dt);
}

void TitleState::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//set camera
	target.setView(camera_);

	//draw
	target.draw(world_);
	target.draw(shape_);
}
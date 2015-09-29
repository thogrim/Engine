#include "TitleState.h"
#include "GameState.h"
#include "../Actions/MoveBy.h"
#include "../Actions/Rotate.h"
#include "../Actions/CompositeAction.h"

TitleState::TitleState(Application& app)
	:State(app),
	world_(),
	shape_(sf::Vector2f(100.f,100.f)),
	ac_(),
	ac2_(){
	world_.setCamera(camera_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setPosition(450.f, 250.f);
	shape_.setOrigin(50.f, 50.f);

	//move shape and go to Game State
	ac_.storeAction(new Actions::MoveBy(this, sf::seconds(1.f), shape_, 100.f, 0.f));
	//auto call1 = [this](){
	//	return new GameState(*this);
	//};
	//addStateChangeCallback(ac_, call1);

	//move shape
	ac2_.storeAction(new Actions::MoveBy(this, sf::seconds(1.f), shape_, -300.f, 0.f));

	//move shape and rotate
	Actions::CompositeAction* comp = new Actions::CompositeAction(this);
	Action* a1 = new Actions::MoveBy(comp, sf::seconds(2.f), shape_, 300.f, 0.f);
	Action* a2 = new Actions::Rotate(comp, sf::seconds(1.f), shape_, 90.f);
	Action* a3 = new Actions::MoveBy(comp, sf::seconds(1.5), shape_, 0.f, 30.f);
	comp->addAction(a1);
	comp->addAction(a2);
	comp->addAction(a3);
	ac3_.storeAction(comp);
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
	shape_.setOrigin(50.f, 50.f);
	ac_.storeAction(new Actions::MoveBy(this, sf::seconds(2.f), shape_, 300.f, 0.f));
	//auto call1 = [this](){
	//	return new GameState(*this);
	//};
	//addStateChangeCallback(ac_, call1);
	ac2_.storeAction(new Actions::MoveBy(this, sf::seconds(2.f), shape_, -300.f, 0.f));

	//move shape
	ac2_.storeAction(new Actions::MoveBy(this, sf::seconds(1.f), shape_, -300.f, 0.f));

	//move shape and rotate
	Actions::CompositeAction* comp = new Actions::CompositeAction(this);
	Action* a1 = new Actions::MoveBy(comp, sf::seconds(2.f), shape_, 300.f, 0.f);
	Action* a2 = new Actions::Rotate(comp, sf::seconds(1.f), shape_, 90.f);
	Action* a3 = new Actions::MoveBy(comp, sf::seconds(1.5), shape_, 0.f, 30.f);
	comp->addAction(a1);
	comp->addAction(a2);
	comp->addAction(a3);
	ac3_.storeAction(comp);
}

TitleState::~TitleState(){
}

void TitleState::onKeyPressed(sf::Keyboard::Key key){
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
	case sf::Keyboard::Num3:
		setAction(ac3_);
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
#include "TitleState.h"
#include "GameState.h"
#include "../Application.h"
#include "../Actions/MoveBy.h"

TitleState::TitleState(Application& app)
	:State(app),
	world_(),
	shape_(sf::Vector2f(100.f,100.f)),
	ac_(),
	ac2_(),
	toGameState_(){
	//loadResources();
	world_.setCamera(camera_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setPosition(450.f, 250.f);
	ac_.storeAction(new Actions::MoveBy(*this, sf::seconds(2.f), shape_, 300.f, 0.f));
	toGameState_.set(ac_.getAction());
	ac2_.storeAction(new Actions::MoveBy(*this, sf::seconds(2.f), shape_, -300.f, 0.f));
}

TitleState::~TitleState(){
}

//void TitleState::loadTextures(){
//}
//
//void TitleState::loadFonts(){
//}
//
//void TitleState::loadSound(){
//}

Action* TitleState::checkEnterStateActions(Action* action){
	if (action == toGameState_.get()){
		//toGameState_.wasPerformed_ = true;
		return action;
	}
	//other checkings similar
	else{
		return action->clone();
	}
}

void TitleState::onActionFinish(){
	if (action_ == toGameState_.get()){
		app_.changeState(new GameState(app_));
	}
	else{
		delete action_;
		action_ = nullptr;
	}
}

void TitleState::processKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	//case sf::Keyboard::Return:
	//	app_.changeState(new GameState(app_));
	//	break;
	case sf::Keyboard::Num1:
		//setAction(action1_);
		setAction(ac_.getAction());
		break;
	case sf::Keyboard::Num2:
		setAction(ac2_.getAction());
		break;
	}
}

void TitleState::processResized(const sf::Event::SizeEvent& size){
	//resize state's camera
	float dwidth = size.width - camera_.getSize().x;
	float dheight = size.height - camera_.getSize().y;
	camera_.move(dwidth / 2, dheight / 2);
	camera_.setSize(static_cast<float>(size.width), static_cast<float>(size.height));

	//resize world camera
	world_.resizeCamera(size.width, size.height);
}

void TitleState::update(const sf::Time& dt){
	//update world mouse pos
	//
	//get window mouse pos
	sf::Vector2i mousePos = sf::Mouse::getPosition(app_.getWindow());
	//set window's camera to world's
	sf::View currentView = app_.getWindow().getView();
	app_.getWindow().setView(world_.getCamera());
	//get world's mouse pos
	sf::Vector2f worldMousePos = app_.getWindow().mapPixelToCoords(mousePos);
	//put it into console
	app_ << "World mouse position: " << worldMousePos.x << " " << worldMousePos.y << std::endl;
	//restore current view
	app_.getWindow().setView(currentView);
	//update world's zoom
	app_ << "Current zoom: " << world_.getZoom() << std::endl;

	if (action_)
		action_->update(dt);
	else{
		//update world
		world_.update(dt);
	}
}

void TitleState::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//set camera
	target.setView(camera_);

	//draw
	target.draw(world_);
	target.draw(shape_);
}
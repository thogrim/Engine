#include "GameState.h"
#include "TitleState.h"
#include "../Application.h"
#include "../Actions/MoveBy.h"

GameState::GameState(Application& app)
	:State(app),
	world_(),
	action_(nullptr){
	loadResources();
	world_.setCamera(camera_);
}

GameState::~GameState(){
	if (action_)
		delete action_;
}

void GameState::loadTextures(){
}

void GameState::loadFonts(){
}

void GameState::loadSound(){
}

void GameState::processKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	case sf::Keyboard::Return:
		app_.changeState(new TitleState(app_));
		//Context::instance().changeState(new TitleState(),Action::MoveBy(100.f,200.f,1.f));
		break;
	case sf::Keyboard::A:
		if (!action_)
			action_ = new Actions::MoveBy(camera_,-100.f,-100.f,2.f);
		break;
	}
}

void GameState::processResized(const sf::Event::SizeEvent& size){
	//sf::FloatRect view(0, 0, static_cast<float>(size.width), static_cast<float>(size.height));
	float dwidth = size.width - camera_.getSize().x;
	float dheight = size.height - camera_.getSize().y;
	camera_.move(dwidth / 2, dheight / 2);
	camera_.setSize(static_cast<float>(size.width), static_cast<float>(size.height));
	world_.resizeCamera(size.width, size.height);
}

void GameState::update(const sf::Time& dt){
	//update action if there is any
	if (action_){
		action_->update(dt);
		if (action_->done()){
			delete action_;
			action_ = nullptr;
		}
	}
	//else update state normally
	else{
		world_.update(dt);
	}
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
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//set camera
	target.setView(camera_);

	//draw
	target.draw(world_);
}

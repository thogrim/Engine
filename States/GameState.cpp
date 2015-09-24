#include "GameState.h"

GameState::GameState()
	:State(),
	world_(),
	action_(nullptr){
	camera_ = Context::instance().window_.getView();
	init();
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
		Context::instance().changeState(new TitleState());
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
	camera_.setSize(size.width,size.height);
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
	else
		world_.update(dt);
}

void GameState::render() const{
	//set camera
	Context::instance().window_.setView(camera_);

	//draw
	Context::instance().window_.draw(world_);
}

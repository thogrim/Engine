#include "TitleState.h"

TitleState::TitleState()
	:State(),
	world_(){
	camera_ = Context::instance().window_.getView();
	//camera_.setViewport(sf::FloatRect(0.25, 0.25, 1.f, 1.f));
	init();
}

TitleState::~TitleState(){
}

void TitleState::loadTextures(){
}

void TitleState::loadFonts(){
}

void TitleState::loadSound(){
}

void TitleState::processKeyPressed(sf::Keyboard::Key key){
	switch (key){
	case sf::Keyboard::R:
		world_.resetCamera();
		break;
	case sf::Keyboard::Return:
		Context::instance().changeState(new GameState());
		break;
	}
}

void TitleState::processResized(const sf::Event::SizeEvent& size){
	float dwidth = size.width - camera_.getSize().x;
	float dheight = size.height - camera_.getSize().y;
	camera_.move(dwidth / 2, dheight / 2);
	camera_.setSize(size.width, size.height);
	world_.resizeCamera(size.width, size.height);
}

void TitleState::update(const sf::Time& dt){
	world_.update(dt);
}

void TitleState::render() const{
	//set camera
	Context::instance().window_.setView(camera_);

	//draw
	Context::instance().window_.draw(world_);
}
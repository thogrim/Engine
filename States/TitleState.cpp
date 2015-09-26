#include "TitleState.h"
#include "GameState.h"
#include "../Application.h"

TitleState::TitleState(Application& app)
	:State(app),
	world_(){
	loadResources();
	world_.setCamera(camera_);
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
		app_.changeState(new GameState(app_));
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
	//update world
	world_.update(dt);

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

void TitleState::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//set camera
	target.setView(camera_);

	//draw
	target.draw(world_);
}
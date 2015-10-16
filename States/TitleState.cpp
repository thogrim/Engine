#include "TitleState.h"
#include "GameState.h"
#include "../Actions/Transforms.h"
#include "../Actions/GUI.h"
#include "../Actions/CompositeAction.h"
#include "../Actions/ActionQueue.h"
#include "../GUI/Button.h"

TitleState::TitleState(Application& app)
	:State(app),
	//world_(),
	shape_(sf::Vector2f(100.f,100.f)),
	ac_(),
	ac2_(),
	buttonTex_(new sf::Texture()),
	menuTex_(new sf::Texture()){
	init();
}

TitleState::TitleState(const State& state)
	:State(state),
	//world_(),
	shape_(sf::Vector2f(100.f, 100.f)),
	ac_(),
	ac2_(),
	buttonTex_(new sf::Texture()),
	menuTex_(new sf::Texture()){
	init();
}

TitleState::~TitleState(){
	delete buttonTex_;
	delete menuTex_;
}

void TitleState::init(){
	//world_.setCamera(camera_);
	shape_.setFillColor(sf::Color::Yellow);
	shape_.setPosition(100.f, 200.f);
	shape_.setOrigin(50.f, 50.f);

	storeAction(ac_, new Actions::Rotate(sf::seconds(1.f), shape_, 180.f));

	storeAction(ac2_, new Actions::Rotate(sf::seconds(1.f), shape_, 90.f));

	//rotate shape by 180 deg and go to GameState
	storeAction(ac3_, new Actions::Rotate(sf::seconds(1.f), shape_, 180.f));
	addStateChangeCallback(ac3_, [this](){
		return new GameState(*this);
	});

	//TEST OF GUI COMPONENT
	if (!buttonTex_->loadFromFile("res/img/play.png")){
		std::cout << "sprite for button testing not loaded!\n";
	}
	if (!menuTex_->loadFromFile("res/img/mainmenu.png")){
		std::cout << "sprite for menu testing not loaded!\n";
	}
	//1st button
	GUI::Button* playButton = new GUI::Button();
	playButton->setTexture(*buttonTex_);
	playButton->setPosition(50.f, 100.f);
	storeAction(*playButton, new Actions::Rotate(sf::seconds(1.f), shape_, 90.f));
	//second button
	GUI::Button* playButton2 = new GUI::Button();
	playButton2->setTexture(*buttonTex_);
	playButton2->setPosition(50.f, 150.f);
	storeAction(*playButton2, new Actions::Rotate(sf::seconds(1.f), shape_, -90.f));
	//third button
	GUI::Button* playButton3 = new GUI::Button();
	playButton3->setTexture(*buttonTex_);
	playButton3->setPosition(50.f, 200.f);
	Actions::ActionQueue* queue3 = new Actions::ActionQueue();
	queue3->addAction(new Actions::SetActive(menu_, false));
	queue3->addAction(new Actions::MoveBy(sf::seconds(1.5f), menu_, 0.f, -600.f));
	queue3->addAction(new Actions::MoveBy(sf::seconds(1.5f), menu2_, 0.f, 600.f));
	queue3->addAction(new Actions::SetActive(menu2_, true));
	storeAction(*playButton3, queue3);
	//menu1
	menu_.setTexture(*menuTex_);
	menu_.setPosition(300.f, 100.f);
	menu_.addComponent(playButton);
	menu_.addComponent(playButton2);
	menu_.addComponent(playButton3);
	///////////////

	//second menu button
	GUI::Button* menu2button = new GUI::Button();
	menu2button->setTexture(*buttonTex_);
	menu2button->setPosition(50.f, 100.f);
	Actions::ActionQueue* queue4 = new Actions::ActionQueue();
	queue4->addAction(new Actions::SetActive(menu2_, false));
	queue4->addAction(new Actions::MoveBy(sf::seconds(1.5f), menu2_, 0.f, -600.f));
	queue4->addAction(new Actions::MoveBy(sf::seconds(1.5f), menu_, 0.f, 600.f));
	queue4->addAction(new Actions::SetActive(menu_, true));
	storeAction(*menu2button, queue4);
	//menu2
	menu2_.setTexture(*menuTex_);
	menu2_.setPosition(600.f, -500.f);
	menu2_.addComponent(menu2button);
	menu2_.setActive(false);

	addBehaviourChangeCallback(*playButton3, [this](){
		return new ChooseLevelBehaviour(menu2_);
	});
	addBehaviourChangeCallback(*menu2button, [this](){
		return new MainMenuBehaviour(menu_);
	});
	behaviour_ = new MainMenuBehaviour(menu_);
}

void TitleState::onKeyPressed(sf::Keyboard::Key key){
	switch (key){
	//case sf::Keyboard::R:
	//	world_.resetCamera();
	//	break;
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
	//world_.resizeCamera(size.width, size.height);
}

//
//void TitleState::onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton){
//	menu_.onMouseButtonPressed(mouseButton);
//	menu2_.onMouseButtonPressed(mouseButton);
//}
//
//void TitleState::onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton){
//	menu_.onMouseButtonReleased(mouseButton);
//	menu2_.onMouseButtonReleased(mouseButton);
//}
//
//void TitleState::onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove){
//	menu_.onMouseMoved(mouseMove);
//	menu2_.onMouseMoved(mouseMove);
//}

void TitleState::withActionUpdate(const sf::Time& dt){
	//print world's mouse position and world's camera zoom
	//sf::Vector2f worldMousePos = getMousePos(world_.getCamera());
	//getAppConsole() << "World's mouse position: " << worldMousePos.x << " " << worldMousePos.y << std::endl
	//	<< "Current world zoom: " << world_.getZoom() << std::endl;
}

void TitleState::noActionUpdate(const sf::Time& dt){
	//update world
	//world_.update(dt);
}

void TitleState::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//set camera
	target.setView(camera_);

	//draw
	//target.draw(world_);
	target.draw(shape_);
	//target.draw(*behaviour_);
	target.draw(menu_);
	target.draw(menu2_);
}
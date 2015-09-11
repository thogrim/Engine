#include "Context.h"

Context::Context()
	:window_(sf::RenderWindow(sf::VideoMode(800,600,32),"")),
	states_(),
	debug_(false),
	timePassed_(sf::Time::Zero),
	TimePerFpsUpdate_(sf::seconds(1.f)),
	frameCounter_(0),
	updateCounter_(0),
	fps_(0.f),
	ups_(0.f),
	debugFont_(),
	debugInfo_(){
	if (!debugFont_.loadFromFile("res/fonts/calibri.ttf")){
		std::cout << "Error: could not load debug font! no info will appear on console!\n";
	}
	else{
		debugInfo_.setFont(debugFont_);
		debugInfo_.setString("Hello!");
		debugInfo_.setCharacterSize(20);
		debugInfo_.setPosition(20.f, 20.f);
		debugInfo_.setColor(sf::Color::Yellow);
	}
}

Context& Context::instance(){
	static Context context;
	return context;
}

void Context::pushState(State* state){
	states_.push_back(std::unique_ptr<State>(state));
}

void Context::popState(){
	states_.pop_back();
}

bool Context::isValid() const{
	return window_.isOpen() && !states_.empty();
}

void Context::changeState(State* state){
	popState();
	pushState(state);
}

void Context::changeDebug(){
	debug_ = !debug_;
}

void Context::update(const sf::Time& dt){
	++updateCounter_;
	timePassed_ += dt;
	if (timePassed_ > TimePerFpsUpdate_){
		fps_ = frameCounter_ / timePassed_.asSeconds();
		ups_ = updateCounter_ / timePassed_.asSeconds();
		timePassed_ = sf::Time::Zero;
		frameCounter_ = 0;
		updateCounter_ = 0;
	}
}

void Context::renderDebug(){
	window_.draw(debugInfo_);
}

void Context::render(){
	states_.back()->render();
	if (debug_)
		renderDebug();
	++frameCounter_;
}
#include "Context.h"

Context::Context()
	:window_(/*sf::RenderWindow(*/sf::VideoMode(800,600,32),""/*)*/),
	states_(),
	hasFocus_(true),
	//debug
	debug_(false),
	timePassed_(sf::Time::Zero),
	TimePerFpsUpdate_(sf::seconds(1.f)),
	frameCounter_(0),
	updateCounter_(0),
	fps_(0.f),
	ups_(0.f),
	debugFont_(),
	debugString_(),
	debugInfo_(){
	//setting font and text
	if (!debugFont_.loadFromFile("res/fonts/calibri.ttf")){
		std::cout << "Error: could not load debug font! no info will appear on console!\n";
	}
	else{
		debugInfo_.setFont(debugFont_);
		debugInfo_.setCharacterSize(17);
		//debugInfo_.setPosition(20.f, 20.f);
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

//void Context::addDebugInfo(const std::string& info){
//	debugString_ << info;
//}

std::ostringstream& Context::operator<<(const std::string& info){
	debugString_ << info;
	return debugString_;
}

sf::Vector2i Context::getMousePos(){
	return sf::Mouse::getPosition(window_);
}

void Context::update(const sf::Time& dt){
	debugString_.str(std::string());
	debugString_.clear();

	//updatng fps
	++updateCounter_;
	timePassed_ += dt;
	if (timePassed_ > TimePerFpsUpdate_){
		fps_ = frameCounter_ / timePassed_.asSeconds();
		ups_ = updateCounter_ / timePassed_.asSeconds();
		timePassed_ = sf::Time::Zero;
		frameCounter_ = 0;
		updateCounter_ = 0;
	}

	//adding debug info
	debugString_ << "FPS: " << std::setprecision(3) << fps_ << " UPS:" << std::setprecision(4) << ups_ << " \n";
	debugString_ << "State stack size: " << states_.size() << " \n";
}

void Context::renderDebug(){
	if (debug_){
		debugInfo_.setString(debugString_.str());
		window_.draw(debugInfo_);
	}
	++frameCounter_;
}

//void Context::render(){
//	//states_.back()->render();
//	if (debug_)
//		renderDebug();
//}
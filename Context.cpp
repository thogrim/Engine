#include "Context.h"

Context::Context()
	:window_(sf::VideoMode(),""),
	debug_(false),
	timePassed_(sf::Time::Zero),
	TimePerFpsUpdate_(sf::seconds(1.f)),
	frameCounter_(0),
	updateCounter_(0),
	fps_(0.f),
	ups_(0.f){
}

Context& Context::instance(){
	static Context context;
	return context;
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
	}
}

void Context::renderDebug(){
	//window_draw(console_);
}

void Context::renderState(){
	//window_.draw(states_.back());
	if (debug_)
		renderDebug();
	++frameCounter_;
}
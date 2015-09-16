#include "Application.h"

Application::Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps){
	Context::instance().window_.setSize(sf::Vector2u(width, height));
	//Context::instance().camera_.reset(sf::FloatRect(0.f,0.f,width,height));
	//Context::instance().window_.setView(Context::instance().camera_);
	Context::instance().window_.setTitle(title);
	Context::instance().window_.setFramerateLimit(fps);
	Context::instance().window_.setKeyRepeatEnabled(false);
	Context::instance().pushState(new TitleState());
}

Application::Application()
	:Application(800,600,"Game",60){
}

Application::~Application(){
}

void Application::processEvents(){
	sf::Event ev;
	while (Context::instance().window_.pollEvent(ev)){
		switch (ev.type){

		case sf::Event::Closed:
			Context::instance().window_.close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)//close window
				Context::instance().window_.close();
			else if (ev.key.code == sf::Keyboard::Tab)//turn on/off debug mode
				Context::instance().changeDebug();
			//else if (ev.key.code == sf::Keyboard::R)//reset camera
			//	Context::instance().resetCamera();
			else
				Context::instance().states_.back()->processKeyPressed(ev.key.code);
			break;
		}
	}
}

void Application::update(const sf::Time& dt){
	Context::instance().update(dt);
	Context::instance().states_.back()->update(dt);
}

void Application::render(){
	Context::instance().window_.clear(sf::Color::Black);
	Context::instance().render();
	Context::instance().window_.display();
}

void Application::run(){
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	const sf::Time TimePerUpdate = sf::seconds(1.f / 240.0f);
	const sf::Time MaxAccumulatedTime = sf::seconds(1.f);
	while (Context::instance().isValid()){
		processEvents();
		accumulator += clock.restart();
		accumulator = std::min(std::max(accumulator,sf::Time::Zero), MaxAccumulatedTime);
		while (accumulator > TimePerUpdate && Context::instance().isValid()){
			accumulator -= TimePerUpdate;
			processEvents();
			update(TimePerUpdate);
		}
		render();
	}
}

#include "Application.h"

Application::Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps){
	Context::instance().window_.setSize(sf::Vector2u(width, height));
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
			if (ev.key.code == sf::Keyboard::Escape)
				Context::instance().window_.close();
			else if (ev.key.code == sf::Keyboard::Tab)
				Context::instance().changeDebug();
			//else
			//	Context::instance().forwardKeyPressed(ev.key.code);
			break;
		}
	}
}

void Application::update(const sf::Time& dt){
	Context::instance().update(dt);
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

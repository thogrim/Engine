#include "Application.h"

Application::Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
	/*:circle_(),
	debug_(false)*/{
	Context::instance().window_.setSize(sf::Vector2u(width, height));
	Context::instance().window_.setTitle(title);
	Context::instance().window_.setFramerateLimit(fps);
	Context::instance().window_.setKeyRepeatEnabled(false);
	//Context::instance().window_.setVisible(true);
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
			break;
		//default:
		//	Context::instance().processEvent(ev);
		//	break;
		}
	}
}

//void Application::processDebugInput(){
//}

void Application::update(const sf::Time& dt){
	Context::instance().update(dt);
}

//void Application::updateDebug(const sf::Time& dt){
//}

void Application::renderDebug(){
}

void Application::render(){
	Context::instance().window_.clear(sf::Color::Magenta);
	Context::instance().renderState();
	Context::instance().window_.display();
}

void Application::run(){
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	const sf::Time TimePerUpdate = sf::seconds(1.f / 240.0f);

	while (Context::instance().window_.isOpen()){
		processEvents();
		accumulator += clock.restart();
		while (accumulator > TimePerUpdate && Context::instance().window_.isOpen()){
			accumulator -= TimePerUpdate;
			processEvents();
			update(TimePerUpdate);
		}
		//updating when some time is left in accumulator
		update(accumulator);
		render();
	}
}

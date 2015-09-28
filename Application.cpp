#include "Application.h"
#include "ResourcesIDs.h"
#include "States/TitleState.h"

Application::Console::Console()
	:up_(false),
	timeSinceFpsUpdate_(sf::Time::Zero),
	TimePerFpsUpdate_(sf::seconds(1.f)),
	frameCounter_(0),
	updateCounter_(0),
	currentFps_(0.f),
	currentUps_(0.f),
	font_(),
	stream_(),
	text_(){
	if (!font_.loadFromFile("res/fonts/calibri.ttf")){
		std::cout << "Error: could not load console font! no info will appear on console!\n";
	}
	else{
		text_.setFont(font_);
		text_.setCharacterSize(17);
		text_.setColor(sf::Color::Yellow);
	}
}

void Application::Console::update(const sf::Time& dt){
	stream_.str(std::string());
	stream_.clear();

	//updatng fps
	++updateCounter_;
	timeSinceFpsUpdate_ += dt;
	if (timeSinceFpsUpdate_ > TimePerFpsUpdate_){
		currentFps_ = frameCounter_ / timeSinceFpsUpdate_.asSeconds();
		currentUps_ = updateCounter_ / timeSinceFpsUpdate_.asSeconds();
		timeSinceFpsUpdate_ = sf::Time::Zero;
		frameCounter_ = 0;
		updateCounter_ = 0;
	}

	//adding debug info
	stream_ << "FPS: " << std::setprecision(3) << currentFps_ << " UPS:" << std::setprecision(4) << currentUps_ << " \n";
}

Application::Application(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
	:window_(sf::VideoMode(width, height, 32), title),
	hasFocus_(true),
	state_(),
	console_(){
	window_.setFramerateLimit(fps); 
	try{
		ResourcesIDs::readIDs();
	}
	catch (std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
	std::unique_ptr<State> beginState(new TitleState(*this));
	state_ = std::move(beginState);
}

Application::Application()
	:Application(800,600,"Game",60){
}

Application::~Application(){
}

sf::RenderWindow& Application::getWindow(){
	return window_;
}

void Application::changeState(State* state){
	state_.reset(state);
}

std::ostringstream& Application::getConsole(){
	return console_.stream_;
}

std::ostringstream& Application::operator<<(const std::string& info){
	console_.stream_ << info;
	return console_.stream_;
}

void Application::processEvents(){
	sf::Event ev;
	while (window_.pollEvent(ev)){
		switch (ev.type){

		case sf::Event::Closed:
			window_.close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)//close window
				window_.close();
			else if (ev.key.code == sf::Keyboard::Tab)//turn on/off concole
				console_.up_ = !console_.up_;
			else
				state_->onKeyPressed(ev.key.code);
			break;

		case sf::Event::Resized:
			state_->onResized(ev.size);
			break;

		case sf::Event::LostFocus:
			hasFocus_ = false;
			break;

		case sf::Event::GainedFocus:
			hasFocus_ = true;
			break;
		}
	}
}

void Application::update(const sf::Time& dt){
	if (hasFocus_){
		console_.update(dt);
		state_->update(dt);
	}
}

void Application::render(){
	if (hasFocus_){
		++console_.frameCounter_;
		window_.clear(sf::Color::Black);
		window_.draw(*state_);
		if (console_.up_){
			console_.text_.setString(console_.stream_.str());
			window_.draw(console_.text_);
		}
		window_.display();
	}
}

void Application::run(){
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	const sf::Time TimePerUpdate = sf::seconds(1.f / 240.0f);
	const sf::Time MaxAccumulatedTime = sf::seconds(1.f);
	while (window_.isOpen() && state_){
		processEvents();
		accumulator += clock.restart();
		accumulator = std::min(std::max(accumulator,sf::Time::Zero), MaxAccumulatedTime);
		while (accumulator > TimePerUpdate && window_.isOpen() && state_){
			accumulator -= TimePerUpdate;
			processEvents();
			update(TimePerUpdate);
		}
		render();
	}
}

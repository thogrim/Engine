#include "World.h"

World::World()
	:bounds_(600.f,400.f),
	camera_(Context::instance().window_.getDefaultView()),
	cameraSpeed_(300.f,300.f),
	currentZoom_(1.f),
	zoomSpeed_(0.99f),
	maxZoomIn_(0.1f),
	maxZoomOut_(10.f){
}

World::~World(){
}

void World::resetCamera(){
	camera_ = Context::instance().window_.getDefaultView();
}

void World::update(const sf::Time& dt){
	//updating camera
		//moving
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			camera_.move(0, -cameraSpeed_.y*dt.asSeconds());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			camera_.move(cameraSpeed_.x*dt.asSeconds(),0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			camera_.move(0, cameraSpeed_.y*dt.asSeconds());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			camera_.move(-cameraSpeed_.x*dt.asSeconds(), 0);

		//zooming
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
			currentZoom_ *= zoomSpeed_;
			if (currentZoom_ < maxZoomIn_)
				currentZoom_ = maxZoomIn_;
			else
				camera_.zoom(zoomSpeed_);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
			currentZoom_ /= zoomSpeed_;
			if (currentZoom_ > maxZoomOut_)
				currentZoom_ = maxZoomOut_;
			else
				camera_.zoom(1.f/zoomSpeed_);
		}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::View defaultView = Context::instance().window_.getDefaultView();
	Context::instance().window_.setView(camera_);

	//drawing bounds of the world
	sf::RectangleShape bounds(bounds_);
	bounds.setOutlineColor(sf::Color::Magenta);
	bounds.setOutlineThickness(-5);
	bounds.setFillColor(sf::Color::Transparent);
	target.draw(bounds);

	Context::instance().window_.setView(defaultView);
}


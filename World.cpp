#include "World.h"

World::World()
	:bounds_(600.f,400.f),
	shape_(100,3),
	vshape_(new VisitableRectangleShape(sf::Vector2f(100.f, 50.f))),
	camera_(),
	cameraSpeed_(300.f,300.f),
	currentZoom_(1.f),
	zoomSpeed_(0.99f),
	maxZoomIn_(0.1f),
	maxZoomOut_(10.f),
	entitySystem_(){
	shape_.setOrigin(100.f, 100.f);
	shape_.setFillColor(sf::Color::Green);
	vshape_->setPosition(200.f, 200.f);
	vshape_->setFillColor(sf::Color::Blue);
	//adding entities
	entitySystem_.createRotatingEntity(sf::Vector2f(200.f, 200.f));
	entitySystem_.createStaticEntity(sf::Vector2f(250.f, 200.f));
	entitySystem_.createStaticEntity(sf::Vector2f(300.f, 200.f));
	entitySystem_.createSolidEntity(sf::Vector2f(350.f, 200.f));
}

World::~World(){
}

void World::resizeCamera(unsigned int width, unsigned int height){
	float dwidth = width*currentZoom_ - camera_.getSize().x;
	float dheight = height*currentZoom_ - camera_.getSize().y;
	camera_.move(dwidth / 2, dheight / 2);
	camera_.setSize(width*currentZoom_, height*currentZoom_);
}

void World::setCamera(const sf::View& camera){
	camera_ = camera;
}

const sf::View& World::getCamera() const{
	return camera_;
}

void World::resetCamera(){
	sf::Vector2f newSize = camera_.getSize() / currentZoom_;
	camera_.setSize(newSize);
	camera_.setCenter(newSize / 2.f);
	currentZoom_ = 1.f;
}

float World::getZoom() const{
	return currentZoom_;
}

void World::update(const sf::Time& dt){
	//updating entities
	entitySystem_.update(dt);

	//updating camera
	//moving
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		camera_.move(0, -cameraSpeed_.y*dt.asSeconds());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		camera_.move(cameraSpeed_.x*dt.asSeconds(), 0);
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
			camera_.zoom(1.f / zoomSpeed_);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::View previousView = target.getView();
	target.setView(camera_);

	//drawing bounds of the world
	sf::RectangleShape bounds(bounds_);
	bounds.setOutlineColor(sf::Color::Magenta);
	bounds.setOutlineThickness(-5);
	bounds.setFillColor(sf::Color::Transparent);
	target.draw(bounds);

	//drawing test shape
	target.draw(shape_);
	target.draw(*vshape_);

	//drawing entities
	target.draw(entitySystem_);

	target.setView(previousView);
}


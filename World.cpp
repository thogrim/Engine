#include "World.h"

World::World()
	:bounds_(600.f,400.f),
	player_(),
	camera_(),
	cameraSpeed_(300.f,300.f),
	currentZoom_(1.f),
	zoomSpeed_(0.99f),
	maxZoomIn_(0.1f),
	maxZoomOut_(10.f),
	entitySystem_(player_){
	entitySystem_.createSimpleBehavEntity(sf::Vector2f(300.f,150.f));
	entitySystem_.createRotatingEntity(sf::Vector2f(200.f, 200.f));
	entitySystem_.createStaticEntity(sf::Vector2f(250.f, 200.f));
	entitySystem_.createStaticEntity(sf::Vector2f(300.f, 200.f));
	entitySystem_.createSolidEntity(sf::Vector2f(350.f, 200.f));
	entitySystem_.createSolidEntity(sf::Vector2f(350.f, 370.f));
	entitySystem_.createAnimatedEntity(sf::Vector2f(400.f, 200.f));
	//entitySystem_.createSolidMovingEntity(sf::Vector2f(400.f, 100.f));
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

bool World::playerCollided() const{
	return entitySystem_.playerCollided_;
}


void World::onKeyPressed(sf::Keyboard::Key key){
	player_.onKeyPressed(key);
}

void World::onKeyReleased(sf::Keyboard::Key key){
	player_.onKeyReleased(key);
}

void World::update(const sf::Time& dt){
	//process events
	entitySystem_.processEvents();
	//update entities
	entitySystem_.update(dt);

	//update player
	player_.update(dt);

	//check if entities in sight of player collide
	entitySystem_.checkPlayerCollisions();

	//update player's sight
	entitySystem_.updatePlayerSight();

	//check player collisions
	//entitySystem_.checkPlayerCollisions();

	//updating camera
	//
	//set camera position to player's
	camera_.setCenter(player_.getMiddle());

	////moving
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	camera_.move(0, -cameraSpeed_.y*dt.asSeconds());
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	camera_.move(cameraSpeed_.x*dt.asSeconds(), 0);
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	camera_.move(0, cameraSpeed_.y*dt.asSeconds());
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	camera_.move(-cameraSpeed_.x*dt.asSeconds(), 0);

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

	//drawing entities
	target.draw(entitySystem_);

	//drawing player
	target.draw(player_);

	target.setView(previousView);
}


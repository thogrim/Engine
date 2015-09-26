#include "World.h"

World::World()
	:bounds_(600.f,400.f),
	shape_(100,3),
	vshape_(sf::Vector2f(100.f, 50.f)),
	//rshape_(sf::Vector2f(100.f, 50.f)),
	camera_(),
	cameraSpeed_(300.f,300.f),
	currentZoom_(1.f),
	zoomSpeed_(0.99f),
	maxZoomIn_(0.1f),
	maxZoomOut_(10.f){
	//shape_.setPosition(200, 100);
	shape_.setOrigin(100.f, 100.f);
	shape_.setFillColor(sf::Color::Green);
	vshape_.setPosition(200.f, 200.f);
	//vshape_.setOrigin(100.f, 100.f);
	vshape_.setFillColor(sf::Color::Blue);
	//rshape_.setPosition(200.f, 300.f);
	////vshape_.setOrigin(100.f, 100.f);
	//rshape_.setFillColor(sf::Color::Red);
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
	//camera_ = Context::instance().window_.getView();
	sf::Vector2f newSize = camera_.getSize() / currentZoom_;
	camera_.setSize(newSize);
	camera_.setCenter(newSize / 2.f);
	currentZoom_ = 1.f;
}
//
//sf::Vector2f World::getWorldMousePos(const sf::RenderWindow& window) const{
//	sf::View currentView = window.getView();
//	window.setView(camera_);
//	sf::Vector2f worldMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//	Context::instance().window_.setView(currentView);
//}

void World::update(const sf::Time& dt){
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

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
	//	std::cout << shape_.getPoint(0).x << " " << shape_.getPoint(0).y << std::endl
	//		<< shape_.getPoint(1).x << " " << shape_.getPoint(1).y << std::endl
	//		<< shape_.getPoint(2).x << " " << shape_.getPoint(2).y << std::endl
	//		<< rshape_.getPoint(0).x << " " << rshape_.getPoint(0).y << std::endl
	//		<< rshape_.getPoint(1).x << " " << rshape_.getPoint(1).y << std::endl
	//		<< rshape_.getPoint(2).x << " " << rshape_.getPoint(2).y << std::endl
	//		<< rshape_.getPoint(3).x << " " << rshape_.getPoint(3).y << std::endl;
	//}

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

	//adding debug info
	//sf::View currentView = Context::instance().window_.getView();
	//Context::instance().window_.setView(camera_);
	//sf::Vector2f worldMousePos = Context::instance().window_.mapPixelToCoords(Context::instance().getMousePos());
	//Context::instance() << "Camera position: " << camera_.getCenter().x << " " << camera_.getCenter().y << "\n"
	//	<< "Camera zoom: " << currentZoom_ << "\n"
	//	<< "Mouse position in world: " << worldMousePos.x << " " << worldMousePos.y << "\n";
	//Context::instance().window_.setView(currentView);
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
	target.draw(vshape_);
	//target.draw(rshape_);

	target.setView(previousView);
}


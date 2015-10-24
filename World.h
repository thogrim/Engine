#pragma once

#include <SFML/Graphics.hpp>
#include "VisitableShapes.h"
#include "Entities/EntitySystem.h"

class World: public sf::Drawable{
public:
	World();
	~World();

	void setCamera(const sf::View& camera);
	const sf::View& getCamera() const;
	void resizeCamera(unsigned int width, unsigned int height);
	void resetCamera();
	float getZoom() const;
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	//physical data
	sf::Vector2f bounds_;
	float gravity_;

	sf::CircleShape shape_;
	std::unique_ptr<VisitableShape> vshape_;

	//world camera
	sf::View camera_;
	sf::Vector2f cameraSpeed_;
	float currentZoom_;
	float zoomSpeed_;
	const float maxZoomIn_;
	const float maxZoomOut_;

	//EntitySystem test
	EntitySystem entitySystem_;
};


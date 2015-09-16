#pragma once

#include <SFML/Graphics.hpp>
#include "Context.h"

class World: public sf::Drawable{
public:
	World();
	~World();

	//void zoomIn();
	//void zoomOut();
	//void moveCamera();
	void resetCamera();
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	//world bounds
	sf::Vector2f bounds_;

	//world camera
	sf::View camera_;
	sf::Vector2f cameraSpeed_;
	float currentZoom_;
	float zoomSpeed_;
	const float maxZoomIn_;
	const float maxZoomOut_;
};


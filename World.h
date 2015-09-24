#pragma once

#include <SFML/Graphics.hpp>
#include "Context.h"
#include "VisitableShapes.h"

class World: public sf::Drawable{
public:
	World();
	~World();

	void resizeCamera(unsigned int width, unsigned int height);
	void resetCamera();
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	//world bounds
	sf::Vector2f bounds_;

	sf::CircleShape shape_;
	VisitableRectangleShape vshape_;

	//world camera
	sf::View camera_;
	sf::Vector2f cameraSpeed_;
	float currentZoom_;
	float zoomSpeed_;
	const float maxZoomIn_;
	const float maxZoomOut_;
};


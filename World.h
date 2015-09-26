/*
	TODO:

	this class should probably have methods like:
	processKeyPressed()
	processResized()
	because code will be clearer

	Entity-like classes might need these methods aswell
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "VisitableShapes.h"

class World: public sf::Drawable{
public:
	World();
	~World();

	void setCamera(const sf::View& camera);
	const sf::View& getCamera() const;
	void resizeCamera(unsigned int width, unsigned int height);
	void resetCamera();
	//sf::Vector2f getWorldMousePos(const sf::RenderWindow& window) const;
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


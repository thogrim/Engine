#pragma once

#include <SFML/Graphics.hpp>
#include "VisitableShapes.h"
#include "Entities/EntitySystem.h"
#include "Entities/Player.h"

class World: public sf::Drawable{
public:
	World();
	~World();

	void setCamera(const sf::View& camera);
	const sf::View& getCamera() const;
	void resizeCamera(unsigned int width, unsigned int height);
	void resetCamera();
	float getZoom() const;
	bool playerCollided() const;

	void onKeyPressed(sf::Keyboard::Key key);
	void onKeyReleased(sf::Keyboard::Key key);
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	//physical data
	sf::Vector2f bounds_;

	Player player_;

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


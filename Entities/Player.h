#pragma once

#include <SFML/Graphics.hpp>
#include "../VisitableShapes.h"

struct CollisionComponent;

class Player: public sf::Transformable, public sf::Drawable{
public:
	Player();
	~Player();

	void onKeyPressed(sf::Keyboard::Key key);
	void onKeyReleased(sf::Keyboard::Key key);

	const VisitableRectangleShape& getShape() const;
	const sf::Vector2f& getMiddle() const;

	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	//PlayerBehaviour* behaviour_;
	VisitableRectangleShape hitbox_;
	sf::Texture* playerTex_;
	sf::Sprite sprite_;
	//or components? spriteComp, collisionComp...
	sf::Vector2f velocity_;
	const float playerVel_;
};
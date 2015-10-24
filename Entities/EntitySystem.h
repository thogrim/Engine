#pragma once

#include <queue>
#include <SFML/Graphics/RenderTarget.hpp>
#include "ComponentSystems.h"
#include "../VisitableShapes.h"
//for textures
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>
#include <vector>
////

class EntitySystem: public sf::Drawable{
public:
	EntitySystem();
	EntitySystem(const EntitySystem&) = delete;
	EntitySystem& operator=(const EntitySystem&) = delete;
	~EntitySystem() = default;

	//entity creation for testing
	void createRotatingEntity(const sf::Vector2f& position);
	void createStaticEntity(const sf::Vector2f& position);
	void createSolidEntity(const sf::Vector2f& position);
	void removeEntity(unsigned int ID);

private:
	unsigned int getNewID();

public:
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	//Systems
	TransformSystem transformSystem_;
	VelocitySystem velocitySystem_;
	RotateSystem rotateSystem_;
	CollisionSystem collisionSystem_;
	SpriteSystem spriteSystem_;

	//ID tracking
	unsigned int lastID_;
	std::queue<unsigned int> freeIDs_;

	//drawing hitboxes
	bool drawHitboxes_;

	//textures for testing
	std::vector<std::unique_ptr<sf::Texture>> textures_;
	//
};
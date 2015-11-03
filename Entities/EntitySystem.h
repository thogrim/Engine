#pragma once

#include <queue>
#include <SFML/Graphics/RenderTarget.hpp>
#include "ComponentSystems.h"
#include "../VisitableShapes.h"
#include "../ShapeVisitors/CollisionVisitor.h"
//for textures
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>
#include <vector>
////

//for updating players sight
#include "../PlayerSight.h"
#include "../ShapeVisitors/PlayerSightVisitor.h"
//and collision
#include "../ShapeVisitors/PlayerCollisionVisitor.h"

//for behaviour test
#include "EntityBehaviours/Wait.h"
//

class Player;

class EntitySystem: public sf::Drawable{
public:
	EntitySystem(Player& player);
	EntitySystem(const EntitySystem&) = delete;
	EntitySystem& operator=(const EntitySystem&) = delete;
	~EntitySystem() = default;

	//entity creation for testing; entity reation will be changed later
	//these methods are temporary
	void createRotatingEntity(const sf::Vector2f& position);
	void createStaticEntity(const sf::Vector2f& position);
	void createSolidEntity(const sf::Vector2f& position);
	void createAnimatedEntity(const sf::Vector2f& position);
	void createSolidMovingEntity(const sf::Vector2f& position);
	void createSimpleBehavEntity(const sf::Vector2f& position);
	//entity remove
	void removeEntity(unsigned int ID);

	void checkPlayerCollisions();
	void updatePlayerSight();
	void pushEvent(const EntityEvent& ev);

private:
	//unsigned int getNewID();
	void getNewID();
	//those methods dont check lastID_ validity
	//t has to be done in createXEntity methods
	void addTransformComponent(const sf::Vector2f& position);
	void addVelocityComponent(const sf::Vector2f& velocity);
	void addRotateComponent(float rotationVelocity);
	void addCollisionComponent(VisitableShape* shape);
	void addSpriteComponent(const sf::Texture& texture);
	void addAnimationComponent(const sf::Vector2i& frameSize, unsigned int nFrames, const sf::Time& frameDuration);
	void addAiComponent(const std::initializer_list<EntityBehaviour*>& behaviours);
public:
	void processEvents();
	void update(const sf::Time& dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	//Systems
	TransformSystem transformSystem_;
	VelocitySystem velocitySystem_;
	RotateSystem rotateSystem_;
	CollisionSystem collisionSystem_;
	SpriteSystem spriteSystem_;
	AnimationSystem animationSystem_;
	AISystem aiSystem_;

	//ID tracking
	unsigned int lastID_;
	std::queue<unsigned int> freeIDs_;

	//drawing hitboxes
	bool drawHitboxes_;

	//textures for testing
	std::vector<std::unique_ptr<sf::Texture>> textures_;
	//

	//reference to player
	Player& player_;
	
	//event queue
	std::queue<EntityEvent> eventQueue_;

	//for testing
public:
	bool playerCollided_;
};
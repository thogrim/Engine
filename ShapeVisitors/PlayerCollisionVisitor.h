#pragma once

#include "ShapeVisitor.h"
#include "../Entities/Player.h"
#include "../PlayerSight.h"

struct PlayerCollisionVisitor : public ShapeVisitor{
	PlayerCollisionVisitor(Player& player)
		:player_(player),
		sight_(PlayerSight::NONE),
		collisionHappened_(false){
	}

	void visit(const VisitableCircleShape& entityCirc, const sf::Vector2f& entityPos);
	void visit(const VisitableRectangleShape& entityRect, const sf::Vector2f& entityPos);
	void visit(const VisitableConvexShape& entityConv, const sf::Vector2f& entityPos);

	Player& player_;
	PlayerSight sight_;
	bool collisionHappened_;
};
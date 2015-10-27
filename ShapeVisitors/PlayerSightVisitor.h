#pragma once

#include "ShapeVisitor.h"
#include "../Entities/Player.h"
#include "../PlayerSight.h"

struct PlayerSightVisitor : public ShapeVisitor{
	PlayerSightVisitor(const Player& player)
		:playerShape_(player.getShape()),
		playerPosition_(player.getPosition()),
		sight_(PlayerSight::NONE){
	}

	void visit(const VisitableCircleShape& circ, const sf::Vector2f& position);
	void visit(const VisitableRectangleShape& rect, const sf::Vector2f& position);
	void visit(const VisitableConvexShape& conv, const sf::Vector2f& position);

	const VisitableRectangleShape& playerShape_;
	const sf::Vector2f& playerPosition_;
	PlayerSight sight_;
};